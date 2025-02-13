#include "song.h"

Song::Song(QObject *parent) : QObject(parent)
{}

Song::Song(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre,
           const QStringList &featuringArtists, const QStringList &albumArtists, int year, int length, int trackNum, int id,
           QObject *parent)
    : QObject(parent),
    m_filePath(filePath),
    m_title(title),
    m_artist(artist),
    m_album(album),
    m_genre(genre),
    m_albumArtists(albumArtists),
    m_featuringArtists(featuringArtists),
    m_length(length),
    m_trackNum(trackNum),
    m_year(year),
    m_id(id) {}

SongData Song::toSongData() const {
    return SongData(m_filePath, m_title, m_artist, m_album, m_genre, m_albumArtists, m_featuringArtists, m_length, m_trackNum, m_year, m_id);
}

void Song::fromSongData(const SongData &data) {
    m_filePath = data.filePath;
    m_title = data.title;
    m_artist = data.artist;
    m_album = data.album;
    m_genre = data.genre;
    m_albumArtists = data.albumArtists;
    m_featuringArtists = data.featuringArtists;
    m_length = data.length;
    m_trackNum = data.trackNum;
    m_year = data.year;
    m_id = data.id;
}
