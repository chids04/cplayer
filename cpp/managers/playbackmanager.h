#ifndef PLAYBACKMANAGER_H
#define PLAYBACKMANAGER_H

#include <QObject>
#include "nowplaying.h"
#include "mediaplayercontroller.h"

class PlaybackManager : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(NowPlaying *nowPlaying READ nowPlaying WRITE setNowPlaying NOTIFY nowPlayingChanged)
    Q_PROPERTY(MediaPlayerController *mediaPlayer READ mediaPlayer WRITE setMediaPlayer NOTIFY mediaPlayerChanged)

public:
    PlaybackManager(QObject *parent=nullptr);
    NowPlaying *nowPlaying() const;
    void setNowPlaying(NowPlaying *newNowPlaying);
    MediaPlayerController *mediaPlayer() const;
    void setMediaPlayer(MediaPlayerController *newMediaPlayer);
    void saveToSettings();
    void loadFromSettings();

signals:
    void nowPlayingChanged();
    void mediaPlayerChanged();

private:
    NowPlaying *m_nowPlaying = nullptr;
    MediaPlayerController *m_mediaPlayer = nullptr;
};

#endif // PLAYBACKMANAGER_H
