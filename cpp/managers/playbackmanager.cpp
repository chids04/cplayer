#include "playbackmanager.h"

PlaybackManager::PlaybackManager(QObject *parent) : QObject(parent)
{
    //load nowplaying
    MediaPlayerController *mediaPlayerController = new MediaPlayerController;
    NowPlaying *nowPlaying = new NowPlaying(mediaPlayerController);

    setNowPlaying(nowPlaying);
    setMediaPlayer(mediaPlayerController);

    connect(m_mediaPlayer, &MediaPlayerController::nextSong, m_nowPlaying, &NowPlaying::onNextClicked);
    connect(m_mediaPlayer, &MediaPlayerController::previousSong, m_nowPlaying, &NowPlaying::onPreviousClicked);
    connect(m_mediaPlayer, &MediaPlayerController::checkQueue, m_nowPlaying, &NowPlaying::onCheckQueue);

    connect(m_nowPlaying, &NowPlaying::playSong, m_mediaPlayer, &MediaPlayerController::onPlaySong);
    connect(m_nowPlaying, &NowPlaying::jumpToEnd, m_mediaPlayer, &MediaPlayerController::onJumpToEnd);
    connect(m_nowPlaying, &NowPlaying::positionLoaded, m_mediaPlayer, &MediaPlayerController::onPositionLoaded);
    connect(m_nowPlaying, &NowPlaying::songLoaded, m_mediaPlayer ,&MediaPlayerController::onSongLoaded);
    connect(m_nowPlaying, &NowPlaying::durationLoaded, m_mediaPlayer, &MediaPlayerController::onDurationChanged);


}

NowPlaying *PlaybackManager::nowPlaying() const
{
    return m_nowPlaying;
}

void PlaybackManager::setNowPlaying(NowPlaying *newNowPlaying)
{
    if (m_nowPlaying == newNowPlaying)
        return;
    m_nowPlaying = newNowPlaying;
    emit nowPlayingChanged();
}

MediaPlayerController *PlaybackManager::mediaPlayer() const
{
    return m_mediaPlayer;
}

void PlaybackManager::setMediaPlayer(MediaPlayerController *newMediaPlayer)
{
    if (m_mediaPlayer == newMediaPlayer)
        return;
    m_mediaPlayer = newMediaPlayer;
    emit mediaPlayerChanged();
}

void PlaybackManager::saveToSettings()
{
    m_nowPlaying->saveNowPlaying();
}

void PlaybackManager::loadFromSettings()
{
    m_nowPlaying->loadFromSettings();
}
