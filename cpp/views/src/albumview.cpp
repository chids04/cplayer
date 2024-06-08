#include "albumview.h"

AlbumView::AlbumView(AlbumHolder *albumHolder, QObject *parent) : albumHolder(albumHolder), QObject(parent)
{

}

void AlbumView::loadAlbums()
{
    albumHolder->addToModel();
}
