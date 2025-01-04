#include "albumsongsview.h"

#include <QDebug>

AlbumSongsManager::AlbumSongsManager(QObject *parent) : QObject(parent) {}

AlbumSongsManager &AlbumSongsManager::instance()
{
    static AlbumSongsManager albumSongsView;
    return albumSongsView;
}

QString AlbumSongsManager::albumName() const
{
    return m_albumName;
}

void AlbumSongsManager::setAlbumName(const QString &newAlbumName)
{
    if (m_albumName == newAlbumName)
        return;
    m_albumName = newAlbumName;
    emit albumNameChanged();
}

QStringList AlbumSongsManager::albumArtists() const
{
    return m_albumArtists;
}

void AlbumSongsManager::setAlbumArtists(const QStringList &newAlbumArtists)
{
    m_albumArtists = newAlbumArtists;
    emit albumArtistsChanged();
}

QString AlbumSongsManager::year() const
{
    return m_year;
}

void AlbumSongsManager::setYear(const QString &newYear)
{
    if (m_year == newYear)
        return;
    m_year = newYear;
    emit yearChanged();
}

QString AlbumSongsManager::genre() const
{
    return m_genre;
}

void AlbumSongsManager::setGenre(const QString &newGenre)
{
    if (m_genre == newGenre)
        return;
    m_genre = newGenre;
    emit genreChanged();
}

void AlbumSongsManager::setAlbum(QStringList albumArtists, QString albumName, QString genre, int year, int songCount)
{
    setAlbumArtists(albumArtists);
    setAlbumName(albumName);
    setGenre(genre);
    setYear(QString::number(year));
    setSongCount(QString::number(songCount));

}

QString AlbumSongsManager::songCount() const
{
    return m_songCount;
}

void AlbumSongsManager::setSongCount(const QString &newSongCount)
{
    if (m_songCount == newSongCount)
        return;
    m_songCount = newSongCount;
    emit songCountChanged();
}
