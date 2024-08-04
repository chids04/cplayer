#ifndef MODELHANDLER_H
#define MODELHANDLER_H

#include <QtQml>
#include <QObject>

#include "songfilterproxymodel.h"
#include "albumfilterproxymodel.h"
#include "playlistmodel.h"
#include "playlistsongsmodel.h"
#include "albumsearchfilter.h"
#include "folderlistmodel.h"


class ModelHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(SongFilterProxyModel* songList READ songList WRITE setSongList NOTIFY songListModelChanged)
    Q_PROPERTY(AlbumFilterProxyModel* albumSongs READ albumSongs WRITE setAlbumSongs NOTIFY albumSongsChanged)
    Q_PROPERTY(AlbumSearchFilter* albumList READ albumList WRITE setAlbumList NOTIFY albumListChanged)
    Q_PROPERTY(PlaylistModel* playlistList READ playlistList WRITE setPlaylistList NOTIFY playlistListChanged)
    Q_PROPERTY(PlaylistSongsModel* playlistSongsList READ playlistSongsList WRITE setPlaylistSongsList NOTIFY playlistSongsListChanged)
    Q_PROPERTY(FolderListModel* folderList READ folderList WRITE setFolderList NOTIFY folderListChanged)

public:

    SongFilterProxyModel *songList() const;
    void setSongList(SongFilterProxyModel *newSongList);

    AlbumFilterProxyModel *albumSongs() const;
    void setAlbumSongs(AlbumFilterProxyModel *newAlbumSongs);

    AlbumSearchFilter *albumList() const;
    void setAlbumList(AlbumSearchFilter *newAlbumList);

    PlaylistModel *playlistList() const;
    void setPlaylistList(PlaylistModel *newPlaylistList);

    PlaylistSongsModel *playlistSongsList() const;

    FolderListModel *folderList() const;
    void setFolderList(FolderListModel *newFolderList);

public slots:
    void setPlaylistSongsList(PlaylistSongsModel *newPlaylistSongsList);

signals:
    void songListModelChanged();

    void albumSongsChanged();

    void albumListChanged();

    void playlistListChanged();

    void playlistSongsListChanged();

    void folderListChanged();

private:

    inline static QJSEngine *s_engine = nullptr;
    SongFilterProxyModel *m_songList = nullptr;
    AlbumFilterProxyModel *m_albumSongs = nullptr;
    AlbumSearchFilter *m_albumList = nullptr;
    PlaylistModel *m_playlistList = nullptr;
    PlaylistSongsModel *m_playlistSongsList = nullptr;
    FolderListModel *m_folderList = nullptr;
};

#endif // MODELHANDLER_H
