#include "songview.h"

SongView::SongView(SongHolder *songHolder, QObject *parent) : QObject(parent), songHolder(songHolder)
{

}

void SongView::loadSongs()
{
    songHolder->populateModel();
}
