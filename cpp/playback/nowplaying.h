#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include "song.h"
#include "queue.h"

#include "playlist.h"
#include "queuemodel.h"
#include "queuemodelfilter.h"

#include <QObject>
#include <qqmlintegration.h>

class SongManager;
class SongListModel;
class AlbumListModel;
class MediaPlayerController;

class NowPlaying : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(QueueModel* queueModel READ queueModel WRITE setQueueModel NOTIFY queueModelChanged)
    Q_PROPERTY(QueueModelFilter* queueProxyModel READ queueProxyModel WRITE setQueueProxyModel NOTIFY queueProxyModelChanged)
    Q_PROPERTY(bool shuffle READ shuffle WRITE setShuffle NOTIFY shuffleChanged)
    Q_PROPERTY(bool loop READ loop WRITE setLoop NOTIFY loopChanged)

public:
    explicit NowPlaying(MediaPlayerController *mediaPlayerController, QObject *parent = nullptr);

    QList<std::shared_ptr<QueueEntry>> getPlayedSongs();
    QList<std::shared_ptr<QueueEntry>> getNowPlaying();
    void playFromQueue();
    int getCurrentSongID();
    void loadFromSettings();
    void saveNowPlaying();
    void setModels(SongManager *songManager);

    QueueModel *queueModel() const;
    void setQueueModel(QueueModel *newQueueModel);

    QueueModelFilter *queueProxyModel() const;
    void setQueueProxyModel(QueueModelFilter *newQueueProxyModel);

    bool shuffle() const;
    bool loop() const;

signals:
    void playSong(Song* song);
    void positionLoaded(qint64 position);
    void durationLoaded(qint64 duration);
    void songLoaded(Song* song);
    void jumpToEnd();

    void queueModelChanged();
    void queueProxyModelChanged();

    void shuffleChanged();
    void loopChanged();

public slots:
    void playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue=false);
    void playPlaylist(const Playlist &playlist, bool queue=false);
    void onPreviousClicked(int duration);
    void onNextClicked();
    void queueNext(Song* song);
    void addToQueue(Song* song);
    void playNow(Song* song);
    void moveSong(int from, int to);
    void clearQueue();

    void onRemoveFromNowPlaying(int songID);
    void onCheckQueue();
    void setShuffle(bool newShuffle);
    void setLoop(bool newLoop);

private:
    QList<Queue> m_queues;
    QList<Song*> songQueue;
    std::shared_ptr<QueueEntry> playingSong;

    int currentQueueIndex;


    QueueModel *m_queueModel = nullptr;
    QueueModelFilter *m_queueProxyModel = nullptr;
    QList<std::shared_ptr<QueueEntry>> m_playedSongs;
    SongListModel *m_songListModel;
    AlbumListModel *m_albumListModel;
    MediaPlayerController *m_mediaPlayer;
    bool m_shuffle = false;
    bool m_loop = false;
};

#endif // NOWPLAYING_H
