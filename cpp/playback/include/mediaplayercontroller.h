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
#include <QTextStream>
#include <QMediaMetaData>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/tpropertymap.h>

#include "coverartholder.h"
#include "playlistmanager.h"
#include "songlistmodel.h"

class MediaPlayerController : public QObject {

    Q_OBJECT

    Q_PROPERTY(bool playing READ playing WRITE playPause NOTIFY playingChanged)

    Q_PROPERTY(QString trackTitle READ trackTitle NOTIFY trackTitleChanged)
    Q_PROPERTY(QString leadingArtist READ leadingArtist NOTIFY leadingArtistChanged)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
    Q_PROPERTY(QStringList features READ features WRITE setFeatures NOTIFY featuresChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    //could use signal and slot instead of passing around object pointers
    explicit MediaPlayerController(const CoverArtHolder *coverArtHolder, PlaylistManager *playlistManager, SongListModel *songModel,  QObject *parent = nullptr);

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
    void setPosition(qint64 newPosition);
    void setFilePath(const QString &newFilePath);

    void playPause(bool newPlaying);
    void setAlbum(const QString &newAlbum);



    void setFeatures(const QStringList &newFeatures);

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
    void albumChanged();
    void volumeChanged();
    void featuresChanged();

public slots:
    void onPositionChanged();
    void onPlayingChanged();
    void queueNext();
    void queuePrevious();
    void togglePlayState();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

    void setSong(QString filePath, QString title, QString artist, QString album, QStringList features);
    void setVolume(float newVolume);

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
    PlaylistManager *playlistManager;
    SongListModel *songModel;
    const CoverArtHolder *coverArtHolder;

    void setTrackTitle(QString &title);
    void setLeadingArtist(QString &leadingArtist);
    void setCoverArt(QPixmap coverArt);

    //current song
    //current song image
    //current song artist

    bool m_playing = false;
    qreal currentDuration;
    float m_volume;
    qint64 m_position;
    qint64 m_duration;


};

#endif // MEDIAPLAYERCONTROLLER_H
