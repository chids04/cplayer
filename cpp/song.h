#ifndef SONG_H
#define SONG_H

#include <QUrl>
#include <QPixmap>
#include <QString>
#include <QObject>
#include <QStringList>

#include <vector>
#include <iostream>


// class Song : QObject
// {
//     Q_OBJECT

// public:
//     QUrl filePath;
//     std::wstring title;
//     std::wstring artist;
//     std::wstring album;
//     std::vector<std::wstring> featuringArtists;

//     Song(const QUrl &filePath, const std::wstring &title, const std::wstring &artist, const std::wstring &album,
//              const std::vector<std::wstring> &featuringArtists,
//              QObject *parent=nullptr);
// };

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
