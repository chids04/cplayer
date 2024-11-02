#ifndef MEDIAPLAYERCONTROLLER_H
#define MEDIAPLAYERCONTROLLER_H

#include <QtQml>
#include <QUrl>
#include <QPixmap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QMediaPlayer>

#include "song.h"

class MediaPlayerController : public QObject {

    Q_OBJECT

    Q_PROPERTY(bool playing READ playing WRITE playPause NOTIFY playingChanged)

    Q_PROPERTY(QString trackTitle READ trackTitle NOTIFY trackTitleChanged)
    Q_PROPERTY(QString leadingArtist READ leadingArtist NOTIFY leadingArtistChanged)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
    Q_PROPERTY(QStringList features READ features WRITE setFeatures NOTIFY featuresChanged)
    Q_PROPERTY(qint64 duration READ duration  WRITE onDurationChanged NOTIFY durationChanged)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(bool repeat READ repeat WRITE setRepeat NOTIFY repeatChanged)
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    //could use signal and slot instead of passing around object pointers
    explicit MediaPlayerController(QObject *parent = nullptr);
    static MediaPlayerController &instance();

    bool playing() const;

    QString leadingArtist() const;
    QString trackTitle() const;
    QPixmap coverArt() const;
    QString filePath() const;
    QStringList features() const;
    QString album() const;

    qint64 position() const;
    qint64 duration() const;
    float volume() const;
    void setFilePath(const QString &newFilePath);

    void playPause(bool newPlaying);
    void setAlbum(const QString &newAlbum);



    void setFeatures(const QStringList &newFeatures);


    bool repeat() const;

    void setRepeat(bool newRepeat);

    void onDurationChanged(qint64 newDuration);

signals:
    void leadingArtistChanged();
    void trackTitleChanged();
    void coverArtChanged();
    void positionChanged();
    void durationChanged();
    void mediaLoaded();
    void filePathChanged();
    void updateUI();

    void playingChanged();
    void nextSong();
    void previousSong(int duration);
    void albumChanged();
    void volumeChanged();
    void featuresChanged();
    void repeatChanged();
    void resetDuration();

public slots:
    void onPositionChanged();
    void onPlayingChanged();
    void nextClicked();
    void previousClicked();
    void onJumpToEnd();
    void togglePlayState();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    void onPlaySong(std::shared_ptr<Song> song);
    void onSongLoaded(std::shared_ptr<Song> song);
    void onRepeatChanged(bool repeat);
    void onPositionLoaded(qint64 position);
    void onRemoveCurrentPlaying(QString &filePath);
    void setVolume(float newVolume);
    void setPosition(qint64 newPosition);

    QString genTime(qint64 currentTime);


private:
    QString m_leadingArtist;
    QString m_trackTitle;
    QString m_filePath;
    QString m_album;
    QStringList m_features;
    int playlistID;

    QMediaPlayer *player;
    QAudioOutput *output;

    void setTrackTitle(QString &title);
    void setLeadingArtist(QString &leadingArtist);
    void setCoverArt(QPixmap coverArt);

    bool m_playing = false;
    qreal currentDuration;
    float m_volume;
    qint64 m_position;
    qint64 m_duration;
    qint64 posFromFile;

    bool firstSong = true;


    bool m_repeat;
};

#endif // MEDIAPLAYERCONTROLLER_H
