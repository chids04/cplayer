#include "soundcloudmodel.h"
#include "soundcloud.h"
#include "soundcloudsearchworker.h"

#include <QThread>
#include <pybind11/pybind11.h>

SoundcloudModel::SoundcloudModel(QObject *parent)
    : QAbstractListModel{parent}
{
    //wrapper = new SoundcloudWrapper(SC_LIB_PATH);
    dlProcess = new QProcess;
    connect(dlProcess ,&QProcess::finished, this, &SoundcloudModel::onSongDlFinished);
}

int SoundcloudModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(m_results.size());
}

QVariant SoundcloudModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_results.size()))
        return QVariant();

    const SoundcloudItem &item = m_results[index.row()];

    switch (role) {
    case Qt::DisplayRole:
    case TitleRole:
        return QString::fromStdString(item.title);

    case ArtistRole:
        return QString::fromStdString(item.artist);

    case TypeRole:
        return QString::fromStdString(item.type);

    case UrlRole:
        return QString::fromStdString(item.permalink_url);

    case ArtworkUrlRole:
        return QString::fromStdString(item.artwork_url);

    case DurationRole:
        return formatDuration(item.duration);

    case DownloadableRole:
        return item.downloadable;

    case TrackCountRole:
        return item.track_count;
    
    case PlaylistSongsRole:
        return QVariant::fromValue(item.playlist_tracks);
    }

    return QVariant();
}

QHash<int, QByteArray> SoundcloudModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[TypeRole] = "itemType";
    roles[UrlRole] = "url";
    roles[ArtworkUrlRole] = "artworkUrl";
    roles[DurationRole] = "duration";
    roles[DownloadableRole] = "downloadable";
    roles[TrackCountRole] = "trackCount";
    return roles;
}

void SoundcloudModel::setResults(const std::vector<SoundcloudItem>& results)
{
    beginResetModel();
    m_results = results;
    endResetModel();
}

const SoundcloudItem& SoundcloudModel::getItem(int index) const
{
    return m_results[index];
}

QString SoundcloudModel::formatDuration(int64_t milliseconds) const
{
    int seconds = milliseconds / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    return QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QLatin1Char('0'));
}

void SoundcloudModel::newSearch(const QString &query) {
    if (query.isEmpty()) {
        return;
    }

    QThread* searchThread = new QThread(this);
    SoundcloudSearchWorker* worker = new SoundcloudSearchWorker(SC_LIB_PATH, query);
    worker->moveToThread(searchThread);

    connect(searchThread, &QThread::started, worker, &SoundcloudSearchWorker::performSearch);
    connect(worker, &SoundcloudSearchWorker::searchCompleted, this, &SoundcloudModel::handleSearchResults);
    connect(worker, &SoundcloudSearchWorker::searchCompleted, searchThread, &QThread::quit);
    connect(worker, &SoundcloudSearchWorker::searchCompleted, worker, &QObject::deleteLater);
    connect(searchThread, &QThread::finished, searchThread, &QObject::deleteLater);
    connect(searchThread, &QThread::finished, this, &SoundcloudModel::searchEnd);

    emit searchStart();
    searchThread->start();
    //auto results = wrapper->search(query.toStdString(), 20);
    //setResults(results);

}

void SoundcloudModel::handleSearchResults(const std::vector<SoundcloudItem>& results)
{
    setResults(results);
}


void SoundcloudModel::download(int index)
{
    if(index < 0 || index >= m_results.size()) return;

    SoundcloudItem &item = m_results[index];


    if(dlProcess->state() == QProcess::Running) return;
    QStringList args;

    args << "-l" << QString::fromStdString(item.permalink_url) << "--path" << dlPath;

    dlProcess->start(downloader, args);

    currentDlIdx = index;

    QString type = QString::fromStdString(item.type);
    QString title = QString::fromStdString(item.title);
    QString msg = QString("downloading %1 <b>%2</b>").arg(type, title);
    emit showMsg(msg);
}

void SoundcloudModel::onSongDlFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    if(exitStatus == QProcess::NormalExit){
        //show the ui that it was succesful
        //need to get the download path of the file too,

        if(currentDlIdx != -1 && currentDlIdx < m_results.size()){
            const SoundcloudItem &song = m_results[currentDlIdx];
            QString title = QString::fromStdString(song.title);
            QString path = QDir(dlPath).filePath(title);

            QString type = QString::fromStdString(song.type);
            QString msg = QString("downloaded %1 <b>%2</b>").arg(type, title);

            emit showMsg(msg);
            
            QString folderPath = QDir(dlPath).filePath(title);

            QFileInfo info(folderPath);
            if (info.isDir()) {
                emit scanForMusic(QUrl::fromLocalFile(path));
            }
            //need to force a rescan of download directory
            
            
        }
        
    }
    else{
    }
}