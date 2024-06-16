#include "viewcontroller.h"

ViewController::ViewController(QObject *parent) : QObject(parent) {}

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

void ViewController::playlistsView()
{
    emit playlistsViewSelected();
}

void ViewController::selectPlaylist()
{
    emit playlistSelected();
}
