#include "album.h"

Album::Album(QObject *parent) : QObject(parent){}

Album::Album(QString &name, QStringList &artist, QString &genre, int &year, QObject *parent) :
    name(name), artist(artist), genre(genre), year(year), QObject(parent){}

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

QList<Song*> Album::getSongs() const
{
    return songList;
}

QString Album::getCoverPath() const {
    return coverPath;
}

void Album::setName(const QString &newName) {
    if(name == newName){
        return;
    }

    name = newName;
    emit nameChanged();
}

void Album::setArtist(const QStringList &newArtist) {
    if(artist == newArtist){
        return;
    }
    artist = newArtist;
    emit artistChanged();
}

void Album::setGenre(const QString &newGenre) {
    if(genre == newGenre){
        return;
    }

    genre = newGenre;
    emit genreChanged();
}

void Album::setYear(int newYear) {
    if(year == newYear){
        return;
    }

    year = newYear;
    emit yearChanged();
}

void Album::setCoverPath(const QString &newCoverPath) {
    if(coverPath == newCoverPath){
        return;
    }

    coverPath = newCoverPath;
    emit coverPathChanged();

}

void Album::addSong(Song* song)
{
    songList << song;
    songCount++;
}

void Album::incrementCount()
{
    songCount++;
}

void Album::decrementCount()
{
    songCount--;
}

int Album::getSongCount() const
{
    return songCount;
}


