#ifndef MEDIAPLAYERCONTROLLER_H
#define MEDIAPLAYERCONTROLLER_H

#include <QtQml>
#include <QUrl>
#include <QImage>
#include <QPixmap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/tpropertymap.h>

#include "coverartholder.h"

class MediaPlayerController : public QObject {

    Q_OBJECT

    Q_PROPERTY(int currentSongIndex READ currentSongIndex NOTIFY currentSongIndexChanged)
    Q_PROPERTY(bool playing READ playing WRITE playPause NOTIFY playingChanged)

    Q_PROPERTY(QString trackTitle READ trackTitle NOTIFY trackTitleChanged)
    Q_PROPERTY(QString leadingArtist READ leadingArtist NOTIFY leadingArtistChanged)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
    Q_PROPERTY(QPixmap coverArt READ coverArt NOTIFY coverArtChanged)
    Q_PROPERTY(QStringList features READ features WRITE setFeatures NOTIFY featuresChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    explicit MediaPlayerController(const CoverArtHolder *coverArtHolder, QObject *parent = nullptr);

    int currentSongIndex() const;
    bool playing() const;

    QString leadingArtist() const;
    QString trackTitle() const;
    QPixmap coverArt() const;

    qint64 position() const;
    void setPosition(qint64 newPosition);

    qint64 duration() const;

    QString filePath() const;
    void setFilePath(const QString &newFilePath);


    QPixmap getCoverFromUrl(const char* filePath) const;

    void playPause(bool newPlaying);

    QString album() const;
    void setAlbum(const QString &newAlbum);

    float volume() const;

    QStringList features() const;

    void setFeatures(const QStringList &newFeatures);

signals:
    void currentSongIndexChanged();
    void leadingArtistChanged();
    void trackTitleChanged();
    void coverArtChanged();
    void positionChanged();
    void durationChanged();
    void mediaLoaded();
    void filePathChanged();
    void updateUI();

    void playingChanged();

    void albumChanged();

    void volumeChanged();

    void featuresChanged();

public slots:
    void nextSong();
    void onPositionChanged();
    void setSong(QString filePath, QString title, QString artist, QString album, QStringList features);
    void onPlayingChanged();
    void togglePlayState();
    void setVolume(float newVolume);


private:
    QMediaPlayer *player;
    QAudioOutput *output;
    qreal currentDuration;
    void setTrackTitle(QString &title);
    void setLeadingArtist(QString &leadingArtist);
    void setCoverArt(QPixmap coverArt);
    //current song
    //current song image
    //current song artist

    int m_currentSongIndex = 0;
    bool m_playing = false;
    QString m_leadingArtist;
    QString m_trackTitle;
    QPixmap m_coverArt;
    qint64 m_position;
    qint64 m_duration;
    QString m_filePath;
    const CoverArtHolder *coverArtHolder;
    QString m_album;
    float m_volume;
    QStringList m_features;
};

#endif // MEDIAPLAYERCONTROLLER_H
