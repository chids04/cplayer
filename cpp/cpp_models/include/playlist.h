#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QDebug>
#include <QStringList>

#include "playlistsongsmodel.h"

class Playlist
{
public:
    Playlist(int id, const QString &playlistName, bool hasCover = false);

    void addSong(const QString &url);

    void setSongCount(int songCount);
    void setDuration(int duration);

    int getID() const;
    int getDuration() const;
    int getSongCount() const;
    QString getPlaylistName() const;
    QString getNextSong();
    QString getPreviousSong();
    PlaylistSongsModel* getSongModel() const;
    bool playlistHasCover() const;

    void clearPlaylist();

private:
    int id;
    int duration;
    int songCount;
    int currentIndex = 0;
    bool hasCover = false;
    QString playlistName;
    QStringList songUrls;
    PlaylistSongsModel *playlistSongsModel;

};

#endif // PLAYLIST_H
