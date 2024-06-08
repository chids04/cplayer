#ifndef ALBUMSONGSVIEW_H
#define ALBUMSONGSVIEW_H

#include <QString>
#include <QObject>
#include <QStringList>
#include <QDebug>

class AlbumSongsView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString albumName READ albumName WRITE setAlbumName NOTIFY albumNameChanged)
    Q_PROPERTY(QStringList albumArtists READ albumArtists WRITE setAlbumArtists NOTIFY albumArtistsChanged)
    Q_PROPERTY(QString year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(QString songCount READ songCount WRITE setSongCount NOTIFY songCountChanged)
    Q_PROPERTY(QString genre READ genre WRITE setGenre NOTIFY genreChanged)
public:
    explicit AlbumSongsView(QObject *parent = nullptr);
    QString albumName() const;
    void setAlbumName(const QString &newAlbumName);
    QStringList albumArtists() const;
    void setAlbumArtists(const QStringList &newAlbumArtists);

    QString year() const;
    void setYear(const QString &newYear);

    QString genre() const;
    void setGenre(const QString &newGenre);

    QString songCount() const;
    void setSongCount(const QString &newSongCount);

signals:
    void albumNameChanged();
    void yearChanged();

    void genreChanged();

    void albumArtistsChanged();

    void songCountChanged();

public slots:
    void setAlbum(QStringList albumArtists, QString albumName, QString genre, int year, int songCount);

private:
    QString m_albumName;
    QStringList m_albumArtists;
    QString m_year;
    QString m_genre;
    QString m_songCount;
};

#endif // ALBUMSONGSVIEW_H
