#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QDebug>
#include <QStringList>

#include "playlistsongsmodel.h"

class Playlist
{
public:
    Playlist(int id, const QString &playlistName, SongListModel *songListModel, bool hasCover = false);

    void addSong(const QString &url);
    void clearPlaylist();
    bool playlistHasCover() const;

    void setSongCount(int songCount);
    void setDuration(int duration);

    int getID() const;
    int getDuration() const;
    int getSongCount() const;
    QString getPlaylistName() const;
    PlaylistSongsModel* getSongModel() const;


private:
    int id;
    int duration;
    int songCount;
    int currentIndex = 0;
    bool hasCover = false;
    QString playlistName;
    PlaylistSongsModel *playlistSongsModel;
};

#endif // PLAYLIST_H
