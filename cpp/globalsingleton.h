#ifndef GLOBALSINGLETON_H
#define GLOBALSINGLETON_H

#include <QObject>
#include <QQmlEngine>

#include "songmanager.h"
#include "playbackmanager.h"
#include "playlistmanager.h"
#include "foldermanager.h"
#include "viewcontroller.h"
#include "coverimgprovider.h"
#include "playlistimageprovider.h"
#include "downloadmanager.h"


class GlobalSingleton : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    void init(CoverImgProvider *coverProvider, PlaylistImageProvider *playlistProvider);

    Q_PROPERTY(SongManager *songManager READ songManager WRITE setSongManager NOTIFY songManagerChanged)
    Q_PROPERTY(PlaybackManager *playbackManager READ playbackManager WRITE setPlaybackManager NOTIFY playbackManagerChanged)
    Q_PROPERTY(PlaylistManager *playlistManager READ playlistManager WRITE setPlaylistManager NOTIFY playlistManagerChanged)
    Q_PROPERTY(FolderManager *folderManager READ folderManager WRITE setFolderManager NOTIFY folderManagerChanged)
    Q_PROPERTY(ViewController *viewController READ viewController WRITE setViewController NOTIFY viewControllerChanged)
    Q_PROPERTY(DownloadManager *downloadManager READ downloadManager WRITE setDownloadManager NOTIFY downloadManagerChanged)

    SongManager *songManager() const;
    void setSongManager(SongManager *newSongManager);

    PlaybackManager *playbackManager() const;
    void setPlaybackManager(PlaybackManager *newPlaybackManager);

    PlaylistManager *playlistManager() const;
    void setPlaylistManager(PlaylistManager *newPlaylistManager);

    FolderManager *folderManager() const;
    void setFolderManager(FolderManager *newFolderManager);

    ViewController *viewController() const;
    void setViewController(ViewController *newViewController);

    DownloadManager *downloadManager() const;
    void setDownloadManager(DownloadManager *newDownloadManager);

signals:

    void songManagerChanged();

    void playbackManagerChanged();

    void playlistManagerChanged();

    void folderManagerChanged();

    void viewControllerChanged();

    void downloadManagerChanged();
    void showMsg(const QString &msg);

public slots:
    void save();
    void onMsgRecieved(const QString &msg);

private:
    SongManager *m_songManager = nullptr;
    PlaybackManager *m_playbackManager = nullptr;
    PlaylistManager *m_playlistManager = nullptr;
    FolderManager *m_folderManager = nullptr;
    ViewController *m_viewController;
    DownloadManager *m_downloadManager = nullptr;
};

#endif // GLOBALSINGLETON_H
