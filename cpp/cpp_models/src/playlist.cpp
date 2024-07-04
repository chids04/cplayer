#include "playlist.h"

Playlist::Playlist(int id, const QString &playlistName, SongListModel* songListModel, bool hasCover) : id(id), playlistName(playlistName), hasCover(hasCover)
{
    playlistSongsModel = new PlaylistSongsModel(songListModel);
}

void Playlist::setSongCount(int songCount)
{
    this->songCount = songCount;
}

void Playlist::setDuration(int duration)
{
    this->duration = duration;
}


int Playlist::getID() const
{
    return id;
}

int Playlist::getDuration() const
{
    return duration;
}

int Playlist::getSongCount() const
{
    return songCount;
}

QString Playlist::getPlaylistName() const
{
    return playlistName;
}


PlaylistSongsModel* Playlist::getSongModel() const
{
    return playlistSongsModel;
}

bool Playlist::playlistHasCover() const
{
    return hasCover;
}
