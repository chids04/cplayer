#include "playlistsongsview.h"

PlaylistSongsView &PlaylistSongsView::instance()
{
    static PlaylistSongsView playlistSongsView;
    return playlistSongsView;
}

int PlaylistSongsView::playlistID() const
{
    return m_playlistID;
}

void PlaylistSongsView::setPlaylistID(int newPlaylistID)
{
    if (m_playlistID == newPlaylistID)
        return;
    m_playlistID = newPlaylistID;
    emit playlistIDChanged();
}

bool PlaylistSongsView::hasCover() const
{
    return m_hasCover;
}

void PlaylistSongsView::setHasCover(bool newHasCover)
{
    if (m_hasCover == newHasCover)
        return;
    m_hasCover = newHasCover;
    emit hasCoverChanged();
}

QString PlaylistSongsView::playlistName() const
{
    return m_playlistName;
}

void PlaylistSongsView::setPlaylistName(const QString &newPlaylistName)
{
    if (m_playlistName == newPlaylistName)
        return;
    m_playlistName = newPlaylistName;
    emit playlistNameChanged();
}
