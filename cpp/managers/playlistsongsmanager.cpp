#include "playlistsongsview.h"

PlaylistSongsManager &PlaylistSongsManager::instance()
{
    static PlaylistSongsManager playlistSongsView;
    return playlistSongsView;
}

int PlaylistSongsManager::playlistID() const
{
    return m_playlistID;
}

void PlaylistSongsManager::setPlaylistID(int newPlaylistID)
{
    if (m_playlistID == newPlaylistID)
        return;
    m_playlistID = newPlaylistID;
    emit playlistIDChanged();
}

bool PlaylistSongsManager::hasCover() const
{
    return m_hasCover;
}

void PlaylistSongsManager::setHasCover(bool newHasCover)
{
    if (m_hasCover == newHasCover)
        return;
    m_hasCover = newHasCover;
    emit hasCoverChanged();
}

QString PlaylistSongsManager::playlistName() const
{
    return m_playlistName;
}

void PlaylistSongsManager::setPlaylistName(const QString &newPlaylistName)
{
    if (m_playlistName == newPlaylistName)
        return;
    m_playlistName = newPlaylistName;
    emit playlistNameChanged();
}
