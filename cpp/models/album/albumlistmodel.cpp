#include "albumlistmodel.h"

AlbumListModel::AlbumListModel(QObject *parent) : QAbstractListModel(parent) {
}


void AlbumListModel::addAlbum(const Album &album)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_albums << album;
    endInsertRows();

}

QModelIndex AlbumListModel::findAlbumIndex(const QString &albumName, const QStringList &albumArtists)
{
    for(int row=0; row<m_albums.count(); row++) {
        const Album &album = m_albums.at(row);
        if(album.getName() == albumName && album.getArtist() == albumArtists){
            return index(row);
        }
    }

    return QModelIndex();
}

void AlbumListModel::updateAlbum(Song* song)
{

    for(Album &album: m_albums){
        if(album.getName() == song->m_album && album.getArtist() == song->m_albumArtists){
            album.addSong(song);
            return;
        }
    }
    //album doesnt exist, need to create a new one
    Album album(song->m_album, song->m_albumArtists, song->m_genre, song->m_year);
    album.addSong(song);
    addAlbum(album);
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
            return QVariant::fromValue(album.getSongs());

        case AlbumArtistRole:
            return album.getArtist();

        case AlbumYearRole:
            return album.getYear();

        case AlbumSongCountRole:
            return album.getSongCount();

        case AlbumObjRole:
            return QVariant::fromValue(album);
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
    roles[AlbumObjRole] = "albumObjRole";

    return roles;
}

QList<Album> AlbumListModel::getAlbums()
{
    return m_albums;
}

void AlbumListModel::clear()
{
    if(!m_albums.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_albums.count() - 1);
        m_albums.clear();
        endRemoveRows();

    }
}

void AlbumListModel::decrementAlbum(const QString &albumName, const QStringList &albumArtists)
{
    for (int i = m_albums.size() - 1; i >= 0; --i) {
        if (m_albums[i].getName() == albumName && m_albums[i].getArtist() == albumArtists) {
            m_albums[i].decrementCount();

        }
    }
}

void AlbumListModel::deleteAlbums()
{
    for (int i = m_albums.size() - 1; i >= 0; --i) {
        if (m_albums[i].getSongCount() == 0) {
            beginRemoveRows(QModelIndex(), i, i);
            m_albums.removeAt(i);
            endRemoveRows();
        }
    }
}
