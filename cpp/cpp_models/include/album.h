#ifndef ALBUM_H
#define ALBUM_H

#include <QHash>
#include <QObject>
#include <QStringList>

#include <memory>

#include "songlistmodel.h"

class Album
{

public:
    Album(QString &name, QStringList &artist, QString &genre, int &year);

    QString getName() const;
    QString getGenre() const;
    int getYear() const;
    void addSong(std::shared_ptr<Song> song);
    int getSongCount() const;
    QStringList getArtist() const;
    QList<std::shared_ptr<Song>> getSongs() const;

private:
    QString name;
    QString genre;
    QStringList artist;
    QList<std::shared_ptr<Song>> songList;
    int year;
    int songCount = 0;

    const SongListModel *songListModel;


};

#endif // ALBUM_H
