#include "queuemodel.h"

QueueModel::QueueModel(QObject *parent)
    : QAbstractListModel{parent}
{}

void QueueModel::addToQueue(QVector<std::shared_ptr<Song>> queue_songs)
{
    beginResetModel();
    m_songs.append(queue_songs);
    endResetModel();

}

void QueueModel::addSong(std::shared_ptr<Song> song){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();
}

void QueueModel::clear()
{
    if(!m_songs.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_songs.count() - 1);
        m_songs.clear();
        endRemoveRows();
    }
}

int QueueModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_songs.count();
}

QModelIndex QueueModel::index(int row, int column, const QModelIndex &parent) const {
    Q_UNUSED(parent)

    // Check for a valid row and column
    if (row >= 0 && row < rowCount() && column == 0) {
        return createIndex(row, column);
    } else {
        return QModelIndex(); // Return an invalid index if out of bounds
    }
}

QVariant QueueModel::data(const QModelIndex &index, int role) const {
    if(index.row() < 0 || index.row() >= m_songs.count())
        return QVariant();

    auto song = m_songs[index.row()];

    switch(role){
    case FilePathRole:
        return song->filePath;

    case TitleRole:
        return song->title;

    case ArtistRole:
        return song->artist;

    case AlbumRole:
        return song->album;

    case FeaturingArtistsRole:
        return song->featuringArtists;

    case NumberInAlbumRole:
        return song->trackNum;

    case AlbumArtistsRole:
        return song->albumArtists;

    case SongObjectRole:
        return QVariant::fromValue(song);

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> QueueModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "filePath";
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[FeaturingArtistsRole] = "features";
    roles[NumberInAlbumRole] = "albumNum";
    roles[AlbumArtistsRole] = "albumArtists";
    roles[SongObjectRole] = "songObject";

    return roles;
}

QString QueueModel::getSongTitle(const QString &filePath) const
{
    //add error checking here
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->title;
        }
    }

    return QString();
}

QString QueueModel::getSongArtist(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->artist;
        }
    }

    return QString();
}

QString QueueModel::getSongAlbum(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->album;
        }
    }

    return QString();
}

QStringList QueueModel::getSongFeatures(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->featuringArtists;
        }
    }

    return QStringList();
}

int QueueModel::getSongTrackNum(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->trackNum;
        }
    }

    return 0;
}

QList<std::shared_ptr<Song> > QueueModel::getSongs()
{
    return m_songs;
}

//void QueueModel::removeSong(const QString &filePath)
//{
//    for(int i=m_songs.size() - 1; i>= 0; --i){
//        if(m_songs[i]->filePath == filePath){
//            emit decrementAlbum(m_songs[i]->album, m_songs[i]->albumArtists);
//            emit removeFromPlaylist(m_songs[i]->id);
//            emit removeCurrentPlaying(m_songs[i]->filePath);

//            beginRemoveRows(QModelIndex(), i, i);
//            m_songs.removeAt(i);
//            endRemoveRows();

//            return;
//        }
//    }
//}

//void QueueModel::removeFolderSongs(QString &folderPath)
//{
//    QString songPath;

//    for (int i = m_songs.size() - 1; i >= 0; --i) {
//        songPath = m_songs[i]->filePath;
//        if (songPath.contains(folderPath, Qt::CaseSensitive)) {
//            emit decrementAlbum(m_songs[i]->album, m_songs[i]->albumArtists);
//            emit removeFromPlaylist(m_songs[i]->id);
//            emit removeCurrentPlaying(m_songs[i]->filePath);

//            beginRemoveRows(QModelIndex(), i, i);
//            m_songs.removeAt(i);  // Remove song if its path contains the folderPath
//            endRemoveRows();

//        }
//    }
//}

void QueueModel::onSongAdded(std::shared_ptr<Song> song)
{
    addSong(song);
}


