#include "globalsingleton.h"

GlobalSingleton::GlobalSingleton()
{

}

MediaPlayerController *GlobalSingleton::mediaPlayer() const
{
    return m_mediaPlayer;
}

void GlobalSingleton::setMediaPlayer(MediaPlayerController *newMediaPlayer)
{
    if (m_mediaPlayer == newMediaPlayer)
        return;
    m_mediaPlayer = newMediaPlayer;
    emit mediaPlayerChanged();
}

NowPlaying *GlobalSingleton::nowPlaying() const
{
    return m_nowPlaying;
}

void GlobalSingleton::setNowPlaying(NowPlaying *newNowPlaying)
{
    if (m_nowPlaying == newNowPlaying)
        return;
    m_nowPlaying = newNowPlaying;
    emit nowPlayingChanged();
}



SongFilterProxyModel *GlobalSingleton::songModel() const
{
    return m_songModel;
}

void GlobalSingleton::setSongModel(SongFilterProxyModel *newSongModel)
{
    if (m_songModel == newSongModel)
        return;
    m_songModel = newSongModel;
    emit songModelChanged();
}

AlbumFilterProxyModel *GlobalSingleton::albumSongsModel() const
{
    return m_albumSongsModel;
}

void GlobalSingleton::setAlbumSongsModel(AlbumFilterProxyModel *newAlbumSongsModel)
{
    if (m_albumSongsModel == newAlbumSongsModel)
        return;
    m_albumSongsModel = newAlbumSongsModel;
    emit albumSongsModelChanged();
}

AlbumSearchFilter *GlobalSingleton::albumSearchModel() const
{
    return m_albumSearchModel;
}

void GlobalSingleton::setAlbumSearchModel(AlbumSearchFilter *newAlbumSearchModel)
{
    if (m_albumSearchModel == newAlbumSearchModel)
        return;
    m_albumSearchModel = newAlbumSearchModel;
    emit albumSearchModelChanged();
}

PlaylistModel *GlobalSingleton::playlistModel() const
{
    return m_playlistModel;
}

void GlobalSingleton::setPlaylistModel(PlaylistModel *newPlaylistModel)
{
    if (m_playlistModel == newPlaylistModel)
        return;
    m_playlistModel = newPlaylistModel;
    emit playlistModelChanged();
}

FolderListModel *GlobalSingleton::folderListModel() const
{
    return m_folderListModel;
}

void GlobalSingleton::setFolderListModel(FolderListModel *newFolderListModel)
{
    if (m_folderListModel == newFolderListModel)
        return;
    m_folderListModel = newFolderListModel;
    emit folderListModelChanged();
}

PlaylistFilter *GlobalSingleton::playlistSongsModel() const
{
    return m_playlistSongsModel;
}

void GlobalSingleton::setPlaylistSongsModel(PlaylistFilter *newPlaylistSongsModel)
{
    if (m_playlistSongsModel == newPlaylistSongsModel)
        return;
    m_playlistSongsModel = newPlaylistSongsModel;
    emit playlistSongsModelChanged();
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
