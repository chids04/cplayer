#include "soundcloudmodel.h"


SoundcloudModel::SoundcloudModel(QObject *parent)
    : QAbstractListModel{parent}
{
    wrapper = new SoundcloudWrapper(SC_LIB_PATH);
    dlProcess = new QProcess;
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

void SoundcloudModel::newSearch(const QString &query)
{
    if(query.isEmpty()){
        return;
    }

    setResults(wrapper->search(query.toStdString(), 20));

}

void SoundcloudModel::download(int index)
{
    if(index < 0 || index >= m_results.size()) return;

    SoundcloudItem &item = m_results[index];
    qDebug() << item.artwork_url;

    //std::string command = "scdl -l --path " + path + ' ' + item.permalink_url;

    if(dlProcess->state() == QProcess::Running) return;
    QStringList args;

    args << "-l" << QString::fromStdString(item.permalink_url) << "--path" << R"(C:\Users\c\Music\scdl\)";
    //args << "-l" << QString::fromStdString(item.permalink_url);

    dlProcess->start(downloader, args);
}
