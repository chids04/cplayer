#ifndef ALBUMHOLDER_H
#define ALBUMHOLDER_H

#include <QList>
#include <QString>
#include <QDebug>

#include "album.h"
#include "albumlistmodel.h"

class AlbumHolder
{
public:
    AlbumHolder(AlbumListModel *albumListModel);

    void addAlbum(Album &album);
    bool isExists(QString &name, QStringList &artist) const;
    void addSongToAlbum(QString &url, QString &name, QStringList &artist) ;
    void addToModel();
    void printAlbums();

private:
    QList<Album> albums;
    AlbumListModel *albumListModel;
};

#endif // ALBUMHOLDER_H
