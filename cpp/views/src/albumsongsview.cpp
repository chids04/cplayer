#include "albumsongsview.h"

#include <QDebug>

AlbumSongsView::AlbumSongsView(QObject *parent) : QObject(parent) {}

AlbumSongsView &AlbumSongsView::instance()
{
    static AlbumSongsView albumSongsView;
    return albumSongsView;
}

QString AlbumSongsView::albumName() const
{
    return m_albumName;
}

void AlbumSongsView::setAlbumName(const QString &newAlbumName)
{
    if (m_albumName == newAlbumName)
        return;
    m_albumName = newAlbumName;
    emit albumNameChanged();
}

QStringList AlbumSongsView::albumArtists() const
{
    return m_albumArtists;
}

void AlbumSongsView::setAlbumArtists(const QStringList &newAlbumArtists)
{
    m_albumArtists = newAlbumArtists;
    emit albumArtistsChanged();
}

QString AlbumSongsView::year() const
{
    return m_year;
}

void AlbumSongsView::setYear(const QString &newYear)
{
    if (m_year == newYear)
        return;
    m_year = newYear;
    emit yearChanged();
}

QString AlbumSongsView::genre() const
{
    return m_genre;
}

void AlbumSongsView::setGenre(const QString &newGenre)
{
    if (m_genre == newGenre)
        return;
    m_genre = newGenre;
    emit genreChanged();
}

void AlbumSongsView::setAlbum(QStringList albumArtists, QString albumName, QString genre, int year, int songCount)
{
    setAlbumArtists(albumArtists);
    setAlbumName(albumName);
    setGenre(genre);
    setYear(QString::number(year));
    setSongCount(QString::number(songCount));

}

QString AlbumSongsView::songCount() const
{
    return m_songCount;
}

void AlbumSongsView::setSongCount(const QString &newSongCount)
{
    if (m_songCount == newSongCount)
        return;
    m_songCount = newSongCount;
    emit songCountChanged();
}
