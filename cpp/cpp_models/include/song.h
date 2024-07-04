#ifndef SONG_H
#define SONG_H

#include <QUrl>
#include <QPixmap>
#include <QString>
#include <QObject>
#include <QMetaType>
#include <QStringList>

#include <memory>

struct Song {
    QString filePath;
    QString title;
    QString artist;
    QString album;
    QString genre;
    QStringList albumArtists;
    QStringList featuringArtists;
    int length;
    int trackNum;
    int year;

    Song() {}

    Song(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre,
         const QStringList &featuringArtists, const QStringList &albumArtists, int year, int length, int trackNum);
};

Q_DECLARE_METATYPE(Song)
Q_DECLARE_METATYPE(std::shared_ptr<Song>)
Q_DECLARE_METATYPE(QList<std::shared_ptr<Song>>)
#endif // SONG_H
