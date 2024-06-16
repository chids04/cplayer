#ifndef SONG_H
#define SONG_H

#include <QUrl>
#include <QPixmap>
#include <QString>
#include <QObject>
#include <QStringList>

#include <vector>
#include <iostream>


struct Song {
    QString filePath;
    QString title;
    QString artist;
    QString album;
    QStringList featuringArtists;
    int length;
    int trackNum;

    Song(const QString &filePath, const QString &title, const QString &artist, const QString &album,
         const QStringList &featuringArtists, int length, int trackNum);
};

#endif // SONG_H
