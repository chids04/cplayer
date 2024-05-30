#include "albumholder.h"

AlbumHolder::AlbumHolder(AlbumListModel *albumListModel) : albumListModel(albumListModel) {}

void AlbumHolder::addAlbum(Album &album)
{
    albums << album;
}

bool AlbumHolder::isExists(QString &name, QStringList &artist) const
{
    auto it = std::find_if(albums.begin(), albums.end(), [&name, &artist](const Album& album) {
        return album.getName() == name && album.getArtist() == artist;
    });
    return it != albums.end();
}

void AlbumHolder::addSongToAlbum(QString &url, QString &name, QStringList &artist)
{
    for(Album &album : albums){
        if(album.getName() == name && album.getArtist() == artist){
            album.addSong(url);
        }
    }
}

QStringList AlbumHolder::getSongsInAlbum(const QStringList &artist, const QString &name) const
{
    for(const Album &album : albums){
        if(album.getName() == name && album.getArtist() == artist){
            return album.getSongs();
        }
    }

    return QStringList();
}

void AlbumHolder::addToModel()
{
    for(Album &album : albums){
        albumListModel->addAlbum(album);
    }
}

void AlbumHolder::printAlbums()
{
    for(Album &album : albums){
        qDebug() << "Album Name:"<< album.getName() << "Album Artist:"<< album.getArtist() << "Album Song Count" << album.getSongCount();
    }
}

