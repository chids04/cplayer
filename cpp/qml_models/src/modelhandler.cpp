#include "modelhandler.h"

SongFilterProxyModel *ModelHandler::songList() const
{
    return m_songList;
}

void ModelHandler::setSongList(SongFilterProxyModel *newSongList)
{
    if (m_songList == newSongList)
        return;
    m_songList = newSongList;
    emit songListModelChanged();
}

AlbumFilterProxyModel *ModelHandler::albumSongs() const
{
    return m_albumSongs;
}

void ModelHandler::setAlbumSongs(AlbumFilterProxyModel *newAlbumSongs)
{
    if (m_albumSongs == newAlbumSongs)
        return;
    m_albumSongs = newAlbumSongs;
    emit albumSongsChanged();
}

AlbumSearchFilter *ModelHandler::albumList() const
{
    return m_albumList;
}

void ModelHandler::setAlbumList(AlbumSearchFilter *newAlbumList)
{
    if (m_albumList == newAlbumList)
        return;
    m_albumList = newAlbumList;
    emit albumListChanged();
}

PlaylistModel *ModelHandler::playlistList() const
{
    return m_playlistList;
}

void ModelHandler::setPlaylistList(PlaylistModel *newPlaylistList)
{
    if (m_playlistList == newPlaylistList)
        return;
    m_playlistList = newPlaylistList;
    emit playlistListChanged();
}

PlaylistSongsModel *ModelHandler::playlistSongsList() const
{
    return m_playlistSongsList;
}

void ModelHandler::setPlaylistSongsList(PlaylistSongsModel *newPlaylistSongsList)
{
    if (m_playlistSongsList == newPlaylistSongsList)
        return;
    m_playlistSongsList = newPlaylistSongsList;
    emit playlistSongsListChanged();
}

FolderListModel *ModelHandler::folderList() const
{
    return m_folderList;
}

void ModelHandler::setFolderList(FolderListModel *newFolderList)
{
    if (m_folderList == newFolderList)
        return;
    m_folderList = newFolderList;
    emit folderListChanged();
}

SettingsManager *ModelHandler::settingsManager() const
{
    return m_settingsManager;
}

void ModelHandler::setSettingsManager(SettingsManager *newSettingsManager)
{
    if (m_settingsManager == newSettingsManager)
        return;
    m_settingsManager = newSettingsManager;
    emit settingsManagerChanged();
}

PlaylistFilter *ModelHandler::playlistFilter() const
{
    return m_playlistFilter;
}

void ModelHandler::setPlaylistFilter(PlaylistFilter *newPlaylistFilter)
{
    if (m_playlistFilter == newPlaylistFilter)
        return;
    m_playlistFilter = newPlaylistFilter;
    emit playlistFilterChanged();
}
