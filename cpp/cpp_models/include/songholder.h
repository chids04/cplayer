#ifndef SONGHOLDER_H
#define SONGHOLDER_H

#include <QList>

#include "song.h"
#include "songlistmodel.h"

class SongHolder
{
public:
    SongHolder(SongListModel *songModel);

    void addSong(Song song);
    void populateModel();


private:
    QList<Song> songs;
    SongListModel *songModel;
};

#endif // SONGHOLDER_H
