#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QtQml>
#include <QObject>
#include <QDebug>

#include "albumsongsview.h"
#include "playlistsongsview.h"
#include "folderview.h"

class ViewController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(AlbumSongsView* albumSongsView READ albumSongsView WRITE setAlbumSongsView NOTIFY albumSongsViewChanged)
    Q_PROPERTY(PlaylistSongsView *playlistSongsView READ playlistSongsView WRITE setPlaylistSongsView NOTIFY playlistSongsViewChanged)
    Q_PROPERTY(FolderView *folderView READ folderView WRITE setFolderView NOTIFY folderViewChanged)

public:
    explicit ViewController(QObject *parent = nullptr);
    static ViewController &instance();

    AlbumSongsView *albumSongsView() const;
    void setAlbumSongsView(AlbumSongsView *newAlbumSongsView);

    PlaylistSongsView *playlistSongsView() const;
    void setPlaylistSongsView(PlaylistSongsView *newPlaylistSongsView);

    FolderView *folderView() const;
    void setFolderView(FolderView *newFolderView);

signals:
    void albumSelected();
    void songViewSelected();
    void playlistSelected();
    void albumViewSelected();
    void folderViewChanged();
    void foldersViewSelected();
    void settingsViewSelected();
    void playlistsViewSelected();
    void albumSongsViewChanged();
    void playlistSongsViewChanged();

public slots:
    void songView();
    void albumView();
    void selectAlbum();
    void foldersView();
    void settingsView();
    void playlistsView();
    void selectPlaylist();
private:
    AlbumSongsView *m_albumSongsView = nullptr;
    PlaylistSongsView *m_playlistSongsView = nullptr;
    FolderView *m_folderView = nullptr;
};

#endif // VIEWCONTROLLER_H
