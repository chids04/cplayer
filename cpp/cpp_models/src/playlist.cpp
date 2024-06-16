#include "playlist.h"

Playlist::Playlist(int id, const QString &playlistName, SongListModel* songListModel, bool hasCover) : id(id), playlistName(playlistName), hasCover(hasCover)
{
    playlistSongsModel = new PlaylistSongsModel(songListModel);
}

void Playlist::addSong(const QString &url)
{
    songUrls << url;
}

void Playlist::setSongCount(int songCount)
{
    this->songCount = songCount;
}

void Playlist::setDuration(int duration)
{
    this->duration = duration;
}

void Playlist::clearPlaylist()
{
    currentIndex = 0;
    songUrls.clear();
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

QList<Song> Playlist::getSongs() const
{
    return songs;
}

QString Playlist::getNextSong()
{
    if(currentIndex == 0){
        return songUrls.at(currentIndex++);
    }

    else if(currentIndex < songUrls.size()-1){
        currentIndex++;
        QString nextSong = songUrls.at(currentIndex);
        return nextSong;

    }

    return QString();
}

QString Playlist::getPreviousSong()
{
    if(currentIndex - 1 == -1){
        return QString();
    }
    else{
        return songUrls.at(--currentIndex);
    }
}

PlaylistSongsModel* Playlist::getSongModel() const
{
    return playlistSongsModel;
}

bool Playlist::playlistHasCover() const
{
    return hasCover;
}
