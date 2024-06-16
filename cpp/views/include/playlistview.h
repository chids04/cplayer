#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QObject>
#include <QVariant>

#include "playlist.h"
#include "playlistmodel.h"
#include "playlistsongsmodel.h"

class PlaylistView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(PlaylistSongsModel *playlistSongsModel READ playlistSongsModel WRITE setPlaylistSongsModel NOTIFY playlistSongsModelChanged)
    Q_PROPERTY(int playlistID READ playlistID WRITE setPlaylistID NOTIFY playlistIDChanged)
    Q_PROPERTY(QString playlistName READ playlistName WRITE setPlaylistName NOTIFY playlistNameChanged)
    Q_PROPERTY(bool hasCover READ hasCover WRITE setHasCover NOTIFY hasCoverChanged)

public:
    explicit PlaylistView(PlaylistModel *playlistModel, SongListModel *songListModel, QObject *parent=nullptr);

    PlaylistSongsModel *playlistSongsModel();

    void setPlaylistSongsModel(PlaylistSongsModel *newPlaylistSongsModel);

    QString playlistName() const;

    bool hasCover() const;
    void setHasCover(bool newHasCover);

    int playlistID() const;
    void setPlaylistID(int newPlaylistID);

public slots:
    void addPlaylist(QString playlistName, bool hasCover = false);
    void loadPlaylistSongs(int id);
    void setPlaylistName(const QString &newPlaylistName);
    void addSongToPlaylist(int id, int songIndex);

signals:
    void playlistSongsModelChanged();

    void playlistNameChanged();

    void hasCoverChanged();

    void playlistIDChanged();

private:
    PlaylistModel *playlistModel;
    SongListModel *songListModel;

    int playlistNum = 0;
    PlaylistSongsModel *m_playlistSongsModel;
    QString m_playlistName;
    bool m_hasCover;
    int m_playlistID;
};

#endif // PLAYLISTVIEW_H
