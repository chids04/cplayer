#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QObject>
#include <QVariant>

#include <memory>

#include "playlist.h"
#include "playlistsongsmodel.h"
#include "playlistimageprovider.h"

class PlaylistManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(PlaylistSongsModel *playlistSongsModel READ playlistSongsModel WRITE setPlaylistSongsModel NOTIFY playlistSongsModelChanged)
    Q_PROPERTY(int playlistID READ playlistID WRITE setPlaylistID NOTIFY playlistIDChanged)
    Q_PROPERTY(QString playlistName READ playlistName WRITE setPlaylistName NOTIFY playlistNameChanged)
    Q_PROPERTY(bool hasCover READ hasCover WRITE setHasCover NOTIFY hasCoverChanged)
    Q_PROPERTY(Playlist currentPlaylist READ currentPlaylist WRITE setCurrentPlaylist NOTIFY currentPlaylistChanged)

public:
    explicit PlaylistManager(QObject *parent=nullptr);
    static PlaylistManager &instance();

    PlaylistSongsModel *playlistSongsModel();

    void setPlaylistSongsModel(PlaylistSongsModel *newPlaylistSongsModel);

    QString playlistName() const;

    bool hasCover() const;
    void setHasCover(bool newHasCover);

    int playlistID() const;
    void setPlaylistID(int newPlaylistID);
    void savePlaylists();
    int getPlaylistNum();
    void loadPlaylistNum(int num);

    Playlist currentPlaylist() const;
    void setCurrentPlaylist(const Playlist &newCurrentPlaylist);
    void setPlaylistImageProvider(PlaylistImageProvider *imgProvider);

public slots:
    void addPlaylist(QString playlistName, QUrl coverPath = QUrl(), bool hasCover = false);
    void removePlaylist(int playlistID);
    void loadPlaylistSongs(int id);
    void setPlaylistName(const QString &newPlaylistName);
    void addSongToPlaylist(int id, std::shared_ptr<Song> song);

signals:
    void playlistSongsModelChanged();
    void playlistNameChanged();
    void hasCoverChanged();
    void playlistIDChanged();

    void currentPlaylistChanged();

private:
    int playlistNum = 0;
    PlaylistSongsModel *m_playlistSongsModel;
    QString m_playlistName;
    bool m_hasCover;
    int m_playlistID;
    Playlist m_currentPlaylist;

    PlaylistImageProvider *playlistImageProvider;
};

#endif // PLAYLISTMANAGER_H
