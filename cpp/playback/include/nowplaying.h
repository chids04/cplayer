#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include <QObject>

#include "song.h"
#include "albumholder.h"
#include "songlistmodel.h"
#include "albumlistmodel.h"

class NowPlaying : public QObject
{
    Q_OBJECT

public:
    explicit NowPlaying(SongListModel *songListModel, AlbumListModel *albumListModel, QObject *parent = nullptr);

signals:
    void playSong(std::shared_ptr<Song> song);
    void jumpToEnd();

public slots:
    void playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue=false);
    void onPreviousClicked(int duration);
    void onNextClicked();
    void addToQueue(QString filePath);

private:
    QList<std::shared_ptr<Song>> songQueue;
    int currentIndex = 0;

    SongListModel *songListModel;
    AlbumListModel *albumListModel;
};

#endif // NOWPLAYING_H
