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

QStringList Album::getSongs() const
{
    return songs;
}

void Album::addSong(QString &url)
{
    songs << url;
    songCount++;
}

int Album::getSongCount() const
{
    return songCount;
}


