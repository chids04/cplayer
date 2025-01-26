#ifndef ALBUM_H
#define ALBUM_H

#include <QHash>
#include <QObject>
#include <QStringList>

#include <memory>
#include "song.h"


class Album
{

public:
    Album();
    Album(QString &name, QStringList &artist, QString &genre, int &year);

    QString getName() const;
    QString getGenre() const;
    int getYear() const;
    int getSongCount() const;
    QStringList getArtist() const;
    QList<Song*> getSongs() const;

    void addSong(Song* song);
    void incrementCount();
    void decrementCount();

private:
    QString name;
    QString genre;
    QStringList artist;
    QList<Song*> songList;
    int year;
    int songCount = 0;



};

Q_DECLARE_METATYPE(Album)

#endif // ALBUM_H
