#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QDebug>
#include <QStringList>

class Playlist
{
public:
    Playlist(int id);

    void addSong(const QString &url);
    void setSongCount(int songCount);
    void setDuration(int duration);
    void clearPlaylist();

    int getID() const;
    QString getNextSong();
    QString getPreviousSong();


private:
    QStringList songUrls;
    int songCount;
    int duration;
    int currentIndex = 0;
    int id;

};

#endif // PLAYLIST_H
