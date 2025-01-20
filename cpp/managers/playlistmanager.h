#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QObject>
#include <QVariant>

#include <memory>

#include "song.h"
#include "songlistmodel.h"

#include "playlist.h"
#include "playlistmodel.h"
#include "playlistfilter.h"
#include "playlistimageprovider.h"


class PlaylistManager : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(PlaylistModel *playlistModel READ playlistModel WRITE setPlaylistModel NOTIFY playlistModelChanged)
    Q_PROPERTY(PlaylistFilter *playlistSongs READ playlistSongs WRITE setPlaylistSongs NOTIFY playlistSongsChanged)
    Q_PROPERTY(int playlistID READ playlistID WRITE setPlaylistID NOTIFY playlistIDChanged)
    Q_PROPERTY(Playlist currentPlaylist READ currentPlaylist WRITE setCurrentPlaylist NOTIFY currentPlaylistChanged)

    Q_PROPERTY(bool hasCover READ hasCover WRITE setHasCover NOTIFY hasCoverChanged)
    Q_PROPERTY(QString playlistName READ playlistName WRITE setPlaylistName NOTIFY playlistNameChanged)
    Q_PROPERTY(int songCount READ songCount WRITE setSongCount NOTIFY songCountChanged)



public:
    explicit PlaylistManager(SongListModel *songListModel, PlaylistImageProvider *playlistImageProvider, QObject *parent=nullptr);


    bool hasCover() const;
    void setHasCover(bool newHasCover);

    int playlistID() const;
    void setPlaylistID(int newPlaylistID);
    int getPlaylistNum();
    void loadPlaylistNum(int num);
    void loadFromSettings();
    void saveToSettings();

    void setCurrentPlaylist(const Playlist &newCurrentPlaylist);
    void setPlaylistImageProvider(PlaylistImageProvider *imgProvider);

    PlaylistModel *playlistModel() const;
    void setPlaylistModel(PlaylistModel *newPlaylistModel);

    PlaylistFilter *playlistSongs() const;
    void setPlaylistSongs(PlaylistFilter *newPlaylistSongs);

    int songCount() const;
    void setSongCount(int newSongCount);

    QString playlistName() const;
    void setPlaylistName(const QString &newPlaylistName);

public slots:
    void addPlaylist(const QString &playlistName, int rotation = 0, const QUrl &coverPath = QUrl(), bool hasCover = false);
    void modifyPlaylist(int id, const QString &playlistName, int rotation = 0, const QUrl &coverPath = QUrl(), bool hasCover = false);
    void removePlaylist(int playlistID);
    void loadPlaylistSongs(int id);
    void addSongToPlaylist(int id, std::shared_ptr<Song> song);
    Playlist currentPlaylist() const;


signals:
    void playlistNameChanged();
    void hasCoverChanged();
    void playlistIDChanged();

    void currentPlaylistChanged();

    void playlistModelChanged();

    void playlistSongsChanged();

    void songCountChanged();

private:
    int playlistNum = 0;
    bool m_hasCover;
    int m_playlistID;
    Playlist m_currentPlaylist;

    PlaylistImageProvider *playlistImageProvider;
    PlaylistModel *m_playlistModel = nullptr;
    PlaylistFilter *m_playlistSongs = nullptr;
    int m_songCount;
    QString m_playlistName;
};

#endif // PLAYLISTMANAGER_H

