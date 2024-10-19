#include "playlist.h"

Playlist::Playlist(int id, const QString &playlistName, bool hasCover) : id(id), playlistName(playlistName), hasCover(hasCover)
{}

void Playlist::addSong(int songID)
{
    songs.append(songID);
}

void Playlist::setSongCount(int songCount)
{
    this->songCount = songCount;
}

void Playlist::setDuration(int duration)
{
    this->duration = duration;
}

void Playlist::removeSong(int id)
{
    for(int i=0; i<songs.count(); i++){
        if(songs[i] == id){
            songs.removeAt(i);
        }
    }
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

QList<int> Playlist::getSongIDs() const
{
    return songs;
}

bool Playlist::playlistHasCover() const
{
    return hasCover;
}

bool Playlist::operator==(const Playlist &other) const
{
    return id == other.id &&
           duration == other.duration &&
           songCount == other.songCount &&
           hasCover == other.hasCover &&
           playlistName == other.playlistName &&
           songs == other.songs;
}

QDataStream &operator<<(QDataStream &out, const Playlist &playlist)
{
    out << playlist.id;
    out << playlist.duration;
    out << playlist.songCount;
    out << playlist.hasCover;
    out << playlist.playlistName;
    out << playlist.songs;
    return out;
}

QDataStream &operator>>(QDataStream &in, Playlist &playlist)
{
    in >> playlist.id;
    in >> playlist.duration;
    in >> playlist.songCount;
    in >> playlist.hasCover;
    in >> playlist.playlistName;
    in >> playlist.songs;
    return in;
}
