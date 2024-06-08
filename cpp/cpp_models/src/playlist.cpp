#include "playlist.h"

Playlist::Playlist(int id) : id(id) {}

void Playlist::addSong(const QString &url)
{
    songUrls << url;
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
