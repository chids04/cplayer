#include "songlistmodel.h"
#include <QDebug>

SongListModel::SongListModel(QObject *parent) : QAbstractListModel(parent) {}

void SongListModel::addSong(const Song &song){
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

QVariant SongListModel::data(const QModelIndex &index, int role) const {
    if(index.row() < 0 || index.row() >= m_songs.count())
        return QVariant();

    const Song &song = m_songs[index.row()];
    switch(role){
        case FilePathRole:
            return song.filePath;

        case TitleRole:
            return song.title;

        case ArtistRole:
            return song.artist;

        case AlbumRole:
            return song.album;

        case FeaturingArtistsRole:
            return song.featuringArtists;

        case NumberInAlbumRole:
            return song.trackNum;

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

    return roles;
}

QString SongListModel::getSongTitle(const QString &filePath) const
{
    //add error checking here

    for(const Song &song : m_songs){
        if(song.filePath == filePath){
            return song.title;
        }
    }

    return QString();
}

QString SongListModel::getSongArtist(const QString &filePath) const
{
    for(const Song &song : m_songs){
        if(song.filePath == filePath){
            return song.artist;
        }
    }

    return QString();
}

QString SongListModel::getSongAlbum(const QString &filePath) const
{
    for(const Song &song : m_songs){
        if(song.filePath == filePath){
            return song.album;
        }
    }

    return QString();
}

QStringList SongListModel::getSongFeatures(const QString &filePath) const
{
    for(const Song &song : m_songs){
        if(song.filePath == filePath){
            return song.featuringArtists;
        }
    }

    return QStringList();
}

int SongListModel::getSongTrackNum(const QString &filePath) const
{
    for(const Song &song : m_songs){
        if(song.filePath == filePath){
            return song.trackNum;
        }
    }

    return 0;
}
