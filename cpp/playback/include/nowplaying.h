#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include <QObject>

#include "albumholder.h"
#include "songlistmodel.h"

class NowPlaying : public QObject
{

public:
    explicit NowPlaying(AlbumHolder *albumHolder, SongListModel *songListModel, QObject *parent = nullptr);

public slots:
    QStringList nextSong() const;
    QStringList previousSong() const;
    void playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue=false);
    void addToQueue(QString filePath);

private:
    QStringList songs;
    int currentIndex;
};

#endif // NOWPLAYING_H
