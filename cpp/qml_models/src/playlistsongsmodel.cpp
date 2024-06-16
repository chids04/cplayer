#include "playlistsongsmodel.h"
#include <QDebug>

PlaylistSongsModel::PlaylistSongsModel(QObject *parent) : QAbstractListModel(parent) {}

void PlaylistSongsModel::addSong(QString filePath, QString title, QString artist, QString album, QStringList featuringArtists, int length, int trackNum){
    Song song = Song(filePath, title, artist, album, featuringArtists, length, trackNum);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();
}

void PlaylistSongsModel::clear()
{
    if(!m_songs.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_songs.count() - 1);
        m_songs.clear();
        endRemoveRows();
    }
}

int PlaylistSongsModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_songs.count();
}

QVariant PlaylistSongsModel::data(const QModelIndex &index, int role) const {
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

QHash<int, QByteArray> PlaylistSongsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "filePath";
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[FeaturingArtistsRole] = "features";
    roles[NumberInAlbumRole] = "albumNum";

    return roles;
}

