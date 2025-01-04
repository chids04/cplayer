#ifndef GLOBALSINGLETON_H
#define GLOBALSINGLETON_H

#include <QObject>
#include <QQmlEngine>

#include "mediaplayercontroller.h"
#include "songfilterproxymodel.h"
#include "nowplaying.h"
#include "albumfilterproxymodel.h"
#include "albumsearchfilter.h"
#include "playlistmodel.h"
#include "playlistfilter.h"
#include "folderlistmodel.h"
#include "playlistmanager.h"

class GlobalSingleton
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    //playback
    Q_PROPERTY(MediaPlayerController *mediaPlayer READ mediaPlayer WRITE setMediaPlayer NOTIFY mediaPlayerChanged)
    Q_PROPERTY(NowPlaying *nowPlaying READ nowPlaying WRITE setNowPlaying NOTIFY nowPlayingChanged)

    //models
    Q_PROPERTY(SongFilterProxyModel *songModel READ songModel WRITE setSongModel NOTIFY songModelChanged)
    Q_PROPERTY(AlbumFilterProxyModel *albumSongsModel READ albumSongsModel WRITE setAlbumSongsModel NOTIFY albumSongsModelChanged)
    Q_PROPERTY(AlbumSearchFilter *albumSearchModel READ albumSearchModel WRITE setAlbumSearchModel NOTIFY albumSearchModelChanged)
    Q_PROPERTY(PlaylistModel *playlistModel READ playlistModel WRITE setPlaylistModel NOTIFY playlistModelChanged)
    Q_PROPERTY(FolderListModel *folderListModel READ folderListModel WRITE setFolderListModel NOTIFY folderListModelChanged)
    Q_PROPERTY(PlaylistFilter *playlistSongsModel READ playlistSongsModel WRITE setPlaylistSongsModel NOTIFY playlistSongsModelChanged)

    Q_PROPERTY(PlaylistManager *playlistManager READ playlistManager WRITE setPlaylistManager NOTIFY playlistManagerChanged)





public:
    GlobalSingleton();
    MediaPlayerController *mediaPlayer() const;
    void setMediaPlayer(MediaPlayerController *newMediaPlayer);
    NowPlaying *nowPlaying() const;
    void setNowPlaying(NowPlaying *newNowPlaying);


    SongFilterProxyModel *songModel() const;
    void setSongModel(SongFilterProxyModel *newSongModel);

    AlbumFilterProxyModel *albumSongsModel() const;
    void setAlbumSongsModel(AlbumFilterProxyModel *newAlbumSongsModel);

    AlbumSearchFilter *albumSearchModel() const;
    void setAlbumSearchModel(AlbumSearchFilter *newAlbumSearchModel);

    PlaylistModel *playlistModel() const;
    void setPlaylistModel(PlaylistModel *newPlaylistModel);

    FolderListModel *folderListModel() const;
    void setFolderListModel(FolderListModel *newFolderListModel);

    PlaylistFilter *playlistSongsModel() const;
    void setPlaylistSongsModel(PlaylistFilter *newPlaylistSongsModel);

    PlaylistManager *playlistManager() const;
    void setPlaylistManager(PlaylistManager *newPlaylistManager);

signals:
    void mediaPlayerChanged();
    void nowPlayingChanged();


    void songModelChanged();

    void albumSongsModelChanged();

    void albumSearchModelChanged();

    void playlistModelChanged();

    void folderListModelChanged();

    void playlistSongsModelChanged();

    void playlistManagerChanged();

private:
    MediaPlayerController *m_mediaPlayer = nullptr;
    NowPlaying *m_nowPlaying = nullptr;
    SongFilterProxyModel *m_songModel = nullptr;
    AlbumFilterProxyModel *m_albumSongsModel = nullptr;
    AlbumSearchFilter *m_albumSearchModel = nullptr;
    PlaylistModel *m_playlistModel = nullptr;
    FolderListModel *m_folderListModel = nullptr;
    PlaylistFilter *m_playlistSongsModel = nullptr;
    PlaylistManager *m_playlistManager = nullptr;
};

#endif // GLOBALSINGLETON_H
