#include "viewcontroller.h"

ViewController::ViewController(QObject *parent) : QObject(parent) {}

ViewController &ViewController::instance()
{
    static ViewController viewController;
    return viewController;
}

void ViewController::songView()
{
    emit songViewSelected();
}

void ViewController::albumView()
{
    emit albumViewSelected();
}

void ViewController::selectAlbum()
{
    emit albumSelected();
}

void ViewController::foldersView()
{
    emit foldersViewSelected();
}

void ViewController::settingsView()
{
    emit settingsViewSelected();
}

void ViewController::playlistsView()
{
    emit playlistsViewSelected();
}

void ViewController::selectPlaylist()
{
    emit playlistSelected();
}

AlbumSongsView *ViewController::albumSongsView() const
{
    return m_albumSongsView;
}

void ViewController::setAlbumSongsView(AlbumSongsView *newAlbumSongsView)
{
    if (m_albumSongsView == newAlbumSongsView)
        return;
    m_albumSongsView = newAlbumSongsView;
    emit albumSongsViewChanged();
}

PlaylistSongsView *ViewController::playlistSongsView() const
{
    return m_playlistSongsView;
}

void ViewController::setPlaylistSongsView(PlaylistSongsView *newPlaylistSongsView)
{
    if (m_playlistSongsView == newPlaylistSongsView)
        return;
    m_playlistSongsView = newPlaylistSongsView;
    emit playlistSongsViewChanged();
}

FolderView *ViewController::folderView() const
{
    return m_folderView;
}

void ViewController::setFolderView(FolderView *newFolderView)
{
    if (m_folderView == newFolderView)
        return;
    m_folderView = newFolderView;
    emit folderViewChanged();
}
