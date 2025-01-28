#ifndef SONG_H
#define SONG_H

#include  <QtQml>
#include <QUrl>
#include <QPixmap>
#include <QString>
#include <QObject>
#include <QMetaType>
#include <QStringList>
#include "SongData.h"

class Song : public QObject {

    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString filePath MEMBER m_filePath NOTIFY filePathChanged)
    Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged)
    Q_PROPERTY(QString artist MEMBER m_artist NOTIFY artistChanged)
    Q_PROPERTY(QString album MEMBER m_album NOTIFY albumChanged)
    Q_PROPERTY(QString genre MEMBER m_genre NOTIFY genreChanged)
    Q_PROPERTY(QStringList albumArtists MEMBER m_albumArtists NOTIFY albumArtistsChanged)
    Q_PROPERTY(QStringList featuringArtists MEMBER m_featuringArtists NOTIFY featuringArtistsChanged)
    Q_PROPERTY(int length MEMBER m_length NOTIFY lengthChanged)
    Q_PROPERTY(int trackNum MEMBER m_trackNum NOTIFY trackNumChanged)
    Q_PROPERTY(int year MEMBER m_year NOTIFY yearChanged)
    Q_PROPERTY(int id MEMBER m_id)

public:
    QString m_filePath;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    QStringList m_albumArtists;
    QStringList m_featuringArtists;
    int m_length;
    int m_trackNum;
    int m_year;
    int m_id;


    explicit Song(QObject *parent=nullptr);
    Song(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre,
         const QStringList &featuringArtists, const QStringList &albumArtists, int year, int length, int trackNum, int id,
         QObject *parent = nullptr);

    SongData toSongData() const;       // Convert Song to SongData
    void fromSongData(const SongData &data); // Populate Song from SongData
signals:
    void filePathChanged();
    void titleChanged();
    void artistChanged();
    void albumChanged();
    void genreChanged();
    void albumArtistsChanged();
    void featuringArtistsChanged();
    void lengthChanged();
    void trackNumChanged();
    void yearChanged();
};

#endif // SONG_H
