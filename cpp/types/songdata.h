#ifndef SONGDATA_H
#define SONGDATA_H

#include <QString>
#include <QStringList>
#include <QDataStream>

struct SongData {
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
    int id;

    // Default constructor
    SongData() = default;

    // Parameterized constructor
    SongData(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre,
             const QStringList &albumArtists, const QStringList &featuringArtists, int length, int trackNum, int year, int id)
        : filePath(filePath),
        title(title),
        artist(artist),
        album(album),
        genre(genre),
        albumArtists(albumArtists),
        featuringArtists(featuringArtists),
        length(length),
        trackNum(trackNum),
        year(year),
        id(id) {}

    // Serialization (for writing to a file)
    friend QDataStream &operator<<(QDataStream &out, const SongData &data) {
        out << data.filePath
            << data.title
            << data.artist
            << data.album
            << data.genre
            << data.albumArtists
            << data.featuringArtists
            << data.length
            << data.trackNum
            << data.year
            << data.id;
        return out;
    }

    // Deserialization (for reading from a file)
    friend QDataStream &operator>>(QDataStream &in, SongData &data) {
        in >> data.filePath
            >> data.title
            >> data.artist
            >> data.album
            >> data.genre
            >> data.albumArtists
            >> data.featuringArtists
            >> data.length
            >> data.trackNum
            >> data.year
            >> data.id;
        return in;
    }
};

#endif // SONGDATA_H
