#include "albumlistmodel.h"

AlbumListModel::AlbumListModel(QObject *parent) : QAbstractListModel(parent) {}

void AlbumListModel::addAlbum(const Album &album)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_albums << album;
    endInsertRows();

}

int AlbumListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_albums.count();

}

QVariant AlbumListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_albums.count()){
        return QVariant();
    }

    const Album &album = m_albums[index.row()];

    switch(role) {

        case AlbumNameRole:
            return album.getName();

        case AlbumGenreRole:
            return album.getGenre();

        case AlbumSongsRole:
            return album.getSongs();

        case AlbumArtistRole:
            return album.getArtist();

        case AlbumYearRole:
            return album.getYear();

        case AlbumSongCountRole:
            return album.getSongCount();

        default:
            return QVariant();
    }


}

QHash<int, QByteArray> AlbumListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[AlbumNameRole] = "albumName";
    roles[AlbumGenreRole] = "albumGenre";
    roles[AlbumSongsRole] = "albumSongs";
    roles[AlbumArtistRole] = "albumArtists";
    roles[AlbumYearRole] = "albumYear";
    roles[AlbumSongCountRole] = "albumSongCount";

    return roles;
}

void AlbumListModel::clear()
{
    if(!m_albums.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_albums.count() - 1);
        m_albums.clear();
        endRemoveRows();

    }
}
