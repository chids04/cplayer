#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include "song.h"
#include "queue.h"

#include "playlist.h"

#include <QObject>

class NowPlaying : public QObject
{
    Q_OBJECT

public:
    explicit NowPlaying(QObject *parent = nullptr);
    static NowPlaying &instance();

    QList<std::shared_ptr<Song>> getNowPlaying();
    int getCurrentIndex();
    void loadFromSettings();

signals:
    void playSong(std::shared_ptr<Song> song);
    void positionLoaded(qint64 position);
    void durationLoaded(qint64 duration);
    void songLoaded(std::shared_ptr<Song>);
    void jumpToEnd();

public slots:
    void playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue=false);
    void playPlaylist(Playlist playlist, bool queue=false);
    void onPreviousClicked(int duration);
    void onNextClicked();
    void queueNext(std::shared_ptr<Song> song);
    void addToQueue(std::shared_ptr<Song> song);
    void playNow(std::shared_ptr<Song> song);

private:
    QList<Queue> m_queues;
    QList<std::shared_ptr<Song>> songQueue;
    int currentIndex = 0;

    int currentQueueIndex;


};

#endif // NOWPLAYING_H
