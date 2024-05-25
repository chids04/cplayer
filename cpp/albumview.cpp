#include "albumview.h"

AlbumView::AlbumView(QObject *parent) : QObject(parent) {}

QString AlbumView::albumName() const
{
    return m_albumName;
}

void AlbumView::setAlbumName(const QString &newAlbumName)
{
    if (m_albumName == newAlbumName)
        return;
    m_albumName = newAlbumName;
    emit albumNameChanged();
}

QStringList AlbumView::albumArtists() const
{
    return m_albumArtists;
}

void AlbumView::setAlbumArtists(const QStringList &newAlbumArtists)
{
    m_albumArtists = newAlbumArtists;
    qDebug() << "setting artist";
    emit albumArtistsChanged();
}

QString AlbumView::year() const
{
    return m_year;
}

void AlbumView::setYear(const QString &newYear)
{
    if (m_year == newYear)
        return;
    m_year = newYear;
    emit yearChanged();
}

QString AlbumView::genre() const
{
    return m_genre;
}

void AlbumView::setGenre(const QString &newGenre)
{
    if (m_genre == newGenre)
        return;
    m_genre = newGenre;
    emit genreChanged();
}

void AlbumView::setAlbum(QStringList albumArtists, QString albumName, QString genre, int year, int songCount)
{
    qDebug() << "signal worked";
    setAlbumArtists(albumArtists);
    setAlbumName(albumName);
    setGenre(genre);
    setYear(QString::number(year));
    setSongCount(QString::number(songCount));

}

QString AlbumView::songCount() const
{
    return m_songCount;
}

void AlbumView::setSongCount(const QString &newSongCount)
{
    if (m_songCount == newSongCount)
        return;
    m_songCount = newSongCount;
    emit songCountChanged();
}
