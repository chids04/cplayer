#include "song.h"

#include <QCryptographicHash>

Song::Song(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre, const QStringList &featuringArtists, const QStringList &albumArtists, int year, int length, int trackNum, int id)
    : filePath(filePath), title(title), artist(artist), album(album), genre(genre), featuringArtists(featuringArtists), albumArtists(albumArtists), year(year), length(length), trackNum(trackNum), id(id)  {

    generateSongHash();
}

void Song::generateSongHash()
{
    QString combined = title + artist;
    QByteArray hash = QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha256);
    songHash = QString(hash.toHex());
}

QDataStream &operator<<(QDataStream &out, const Song &song){
    out << song.filePath << song.title << song.artist << song.album
        << song.genre << song.albumArtists << song.featuringArtists
        << song.length << song.trackNum << song.year << song.id << song.songHash;

    return out;
}

QDataStream &operator>>(QDataStream &in, Song &song) {
    in >> song.filePath >> song.title >> song.artist
        >> song.album >> song.genre >> song.albumArtists
        >> song.featuringArtists >> song.length
        >> song.trackNum >> song.year >> song.id >> song.songHash;

    return in;
}
