#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <QDebug>
#include <QMetaType>


class Playlist
{
public:
    Playlist() = default;
    Playlist(int id, const QString &playlistName, bool hasCover = false);

    void addSong(int songID);
    void clearPlaylist();
    bool playlistHasCover() const;

    void setSongCount(int songCount);
    void setDuration(int duration);
    void removeSong(int id);

    int getID() const;
    int getDuration() const;
    int getSongCount() const;
    QString getPlaylistName() const;
    QList<int> getSongIDs() const;

    bool operator==(const Playlist &other) const;

    friend QDataStream &operator<<(QDataStream &out, const Playlist &playlist);
    friend QDataStream &operator>>(QDataStream &in, Playlist &playlist);

private:
    int id;
    int duration;
    int songCount;
    bool hasCover = false;
    QString playlistName;
    QList<int> songs;
};

Q_DECLARE_METATYPE(QList<Playlist>)
Q_DECLARE_METATYPE(Playlist)
Q_DECLARE_METATYPE(std::shared_ptr<Playlist>)

#endif // PLAYLIST_H
