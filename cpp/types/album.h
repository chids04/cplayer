#ifndef ALBUM_H
#define ALBUM_H

#include <QHash>
#include <QObject>
#include <QStringList>

#include "song.h"


class Album : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList artist READ getArtist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString genre READ getGenre WRITE setGenre NOTIFY genreChanged)
    Q_PROPERTY(int year READ getYear WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(QString coverPath READ getCoverPath WRITE setCoverPath NOTIFY coverPathChanged)


public:
    explicit Album(QObject *parent = nullptr);
    Album(QString &name, QStringList &artist, QString &genre, int &year,
        QObject *parent = nullptr);

    QString getName() const;
    QString getGenre() const;
    int getYear() const;
    int getSongCount() const;
    QStringList getArtist() const;
    QList<Song*> getSongs() const;
    QString getCoverPath() const;


    void setName(const QString &newName);
    void setArtist(const QStringList &newArtist);
    void setGenre(const QString &newGenre);
    void setYear(int newYear);
    void setCoverPath(const QString &newCoverPath);


    void addSong(Song* song);
    void incrementCount();
    void decrementCount();

signals:
    void nameChanged();
    void artistChanged();
    void genreChanged();
    void yearChanged();
    void coverPathChanged();

private:
    QString name;
    QString genre;
    QStringList artist;
    QList<Song*> songList;
    int year;
    int songCount = 0;
    QString coverPath;



};

Q_DECLARE_METATYPE(Album)

#endif // ALBUM_H
