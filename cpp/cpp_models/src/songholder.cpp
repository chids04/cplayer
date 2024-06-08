#include "songholder.h"

SongHolder::SongHolder(SongListModel *songModel) : songModel(songModel)
{
}

void SongHolder::addSong(Song song)
{
    songs << song;

}

void SongHolder::populateModel()
{
    songModel->clear();

    for(const Song &song : songs){
        songModel->addSong(song);
    }
}
