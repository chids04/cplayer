#ifndef MUSICHANDLER_H
#define MUSICHANDLER_H

#include <QtQml>
#include <QObject>

#include "nowplaying.h"
#include "playlistmanager.h"
#include "mediaplayercontroller.h"

class MusicHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(NowPlaying* nowPlaying READ nowPlaying WRITE setNowPlaying NOTIFY nowPlayingChanged)
    Q_PROPERTY(MediaPlayerController* mediaPlayerController READ mediaPlayerController WRITE setMediaPlayerController NOTIFY mediaPlayerControllerChanged)
    Q_PROPERTY(PlaylistManager* playlistManager READ playlistManager WRITE setPlaylistManager NOTIFY playlistManagerChanged)

public:
    NowPlaying *nowPlaying() const;
    void setNowPlaying(NowPlaying *newNowPlaying);

    MediaPlayerController *mediaPlayerController() const;
    void setMediaPlayerController(MediaPlayerController *newMediaPlayerController);

    PlaylistManager *playlistManager() const;
    void setPlaylistManager(PlaylistManager *newPlaylistManager);

signals:
    void nowPlayingChanged();

    void mediaPlayerControllerChanged();

    void playlistManagerChanged();

private:
    NowPlaying *m_nowPlaying = nullptr;
    MediaPlayerController *m_mediaPlayerController = nullptr;
    PlaylistManager *m_playlistManager = nullptr;
};

#endif // MUSICHANDLER_H
