#include "songlistmodel.h"
#include <QDebug>

SongListModel::SongListModel(QObject *parent) : QAbstractListModel(parent) {}

SongListModel &SongListModel::instance()
{
    static SongListModel songListModel;
    return songListModel;
}

void SongListModel::addSong(std::shared_ptr<Song> song){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();
}

void SongListModel::clear()
{
    if(!m_songs.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_songs.count() - 1);
        m_songs.clear();
        endRemoveRows();
    }
}

int SongListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_songs.count();
}

QModelIndex SongListModel::index(int row, int column, const QModelIndex &parent) const {
    Q_UNUSED(parent)

    // Check for a valid row and column
    if (row >= 0 && row < rowCount() && column == 0) {
        return createIndex(row, column);
    } else {
        return QModelIndex(); // Return an invalid index if out of bounds
    }
}

QVariant SongListModel::data(const QModelIndex &index, int role) const {
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

        case SongObjectRole:
            return QVariant::fromValue(song);

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> SongListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "filePath";
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[FeaturingArtistsRole] = "features";
    roles[NumberInAlbumRole] = "albumNum";
    roles[SongObjectRole] = "songObject";

    return roles;
}

QString SongListModel::getSongTitle(const QString &filePath) const
{
    //add error checking here
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->title;
        }
    }

    return QString();
}

QString SongListModel::getSongArtist(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->artist;
        }
    }

    return QString();
}

QString SongListModel::getSongAlbum(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->album;
        }
    }

    return QString();
}

QStringList SongListModel::getSongFeatures(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->featuringArtists;
        }
    }

    return QStringList();
}

int SongListModel::getSongTrackNum(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->trackNum;
        }
    }

    return 0;
}

void SongListModel::onSongAdded(std::shared_ptr<Song> song)
{
    addSong(song);
}
