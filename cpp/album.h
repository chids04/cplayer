#ifndef ALBUM_H
#define ALBUM_H

#include <QHash>
#include <QStringList>

class Album
{

public:
    Album(QString &name, QStringList &artist, QString &genre, int &year);

    QString getName() const;
    QString getGenre() const;
    int getYear() const;
    void addSong(QString &url);
    int getSongCount() const;
    QStringList getArtist() const;
    QStringList getSongs() const;

private:
    QString name;
    QString genre;
    QStringList songs;
    QStringList artist;
    int year;
    int songCount = 0;

};

#endif // ALBUM_H
