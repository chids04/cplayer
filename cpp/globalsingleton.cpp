#include "globalsingleton.h"
#include "coverimgprovider.h"

void GlobalSingleton::init(CoverImgProvider *coverProvider, PlaylistImageProvider *playlistProvider)
{
    //init managers
    setPlaybackManager(new PlaybackManager);
    setSongManager(new SongManager(m_playbackManager));
    setPlaylistManager(new PlaylistManager(m_songManager->getSongListModel(), playlistProvider));
    setFolderManager(new FolderManager(m_songManager, coverProvider));
    setViewController(new ViewController);
    setDownloadManager(new DownloadManager);

    //injecting dependencies in cases where there are circular dependencies
    m_playbackManager->nowPlaying()->setModels(m_songManager);
    m_songManager->initPlaylists(m_playlistManager);

    //now load data from settings, start with loading songs since nowplaying depends on it
    m_songManager->loadFromSettings();
    m_playbackManager->loadFromSettings();
    m_folderManager->loadFromSettings();
    m_playlistManager->loadFromSettings();
}

void GlobalSingleton::save()
{
    m_songManager->saveToSettings();
    m_folderManager->saveToSettings();
    m_playbackManager->saveToSettings();
    m_playlistManager->saveToSettings();

}


SongManager *GlobalSingleton::songManager() const
{
    return m_songManager;
}

void GlobalSingleton::setSongManager(SongManager *newSongManager)
{
    if (m_songManager == newSongManager)
        return;
    m_songManager = newSongManager;
    emit songManagerChanged();
}

PlaybackManager *GlobalSingleton::playbackManager() const
{
    return m_playbackManager;
}

void GlobalSingleton::setPlaybackManager(PlaybackManager *newPlaybackManager)
{
    if (m_playbackManager == newPlaybackManager)
        return;
    m_playbackManager = newPlaybackManager;
    emit playbackManagerChanged();
}

PlaylistManager *GlobalSingleton::playlistManager() const
{
    return m_playlistManager;
}

void GlobalSingleton::setPlaylistManager(PlaylistManager *newPlaylistManager)
{
    if (m_playlistManager == newPlaylistManager)
        return;
    m_playlistManager = newPlaylistManager;
    emit playlistManagerChanged();
}

FolderManager *GlobalSingleton::folderManager() const
{
    return m_folderManager;
}

void GlobalSingleton::setFolderManager(FolderManager *newFolderManager)
{
    if (m_folderManager == newFolderManager)
        return;
    m_folderManager = newFolderManager;
    emit folderManagerChanged();
}

ViewController *GlobalSingleton::viewController() const
{
    return m_viewController;
}

void GlobalSingleton::setViewController(ViewController *newViewController)
{
    m_viewController = newViewController;
    emit viewControllerChanged();
}

DownloadManager *GlobalSingleton::downloadManager() const
{
    return m_downloadManager;
}

void GlobalSingleton::setDownloadManager(DownloadManager *newDownloadManager)
{
    if (m_downloadManager == newDownloadManager)
        return;
    m_downloadManager = newDownloadManager;
    emit downloadManagerChanged();
}
