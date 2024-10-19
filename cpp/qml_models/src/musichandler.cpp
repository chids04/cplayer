#include "musichandler.h"

NowPlaying *MusicHandler::nowPlaying() const
{
    return m_nowPlaying;
}

void MusicHandler::setNowPlaying(NowPlaying *newNowPlaying)
{
    if (m_nowPlaying == newNowPlaying)
        return;
    m_nowPlaying = newNowPlaying;
    emit nowPlayingChanged();
}

MediaPlayerController *MusicHandler::mediaPlayerController() const
{
    return m_mediaPlayerController;
}

void MusicHandler::setMediaPlayerController(MediaPlayerController *newMediaPlayerController)
{
    if (m_mediaPlayerController == newMediaPlayerController)
        return;
    m_mediaPlayerController = newMediaPlayerController;
    emit mediaPlayerControllerChanged();
}

PlaylistManager *MusicHandler::playlistManager() const
{
    return m_playlistManager;
}

void MusicHandler::setPlaylistManager(PlaylistManager *newPlaylistManager)
{
    if (m_playlistManager == newPlaylistManager)
        return;
    m_playlistManager = newPlaylistManager;
    emit playlistManagerChanged();
}
