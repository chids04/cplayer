#include "album.h"

Album::Album(QString &name, QStringList &artist, QString &genre, int &year) :
    name(name), artist(artist), genre(genre), year(year){}

QString Album::getName() const
{
    return name;
}

QString Album::getGenre() const
{
    return genre;
}

int Album::getYear() const
{
    return year;
}

QStringList Album::getArtist() const
{
    return artist;
}

QList<std::shared_ptr<Song>> Album::getSongs() const
{
    return songList;
}

void Album::addSong(std::shared_ptr<Song> song)
{
    songList << song;
    songCount++;
}

int Album::getSongCount() const
{
    return songCount;
}


