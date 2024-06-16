#ifndef SONG_H
#define SONG_H

#include <QUrl>
#include <QPixmap>
#include <QString>
#include <QObject>
#include <QMetaType>
#include <QStringList>

struct Song {
    QString filePath;
    QString title;
    QString artist;
    QString album;
    QStringList featuringArtists;
    int length;
    int trackNum;

    Song() {}

    Song(const QString &filePath, const QString &title, const QString &artist, const QString &album,
         const QStringList &featuringArtists, int length, int trackNum);
};

Q_DECLARE_METATYPE(Song)
#endif // SONG_H
