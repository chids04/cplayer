#ifndef QUEUEMODEL_H
#define QUEUEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <deque>

#include "song.h"

struct QueueEntry {
    std::shared_ptr<Song> song;
    int songID;
};

class QueueModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QueueModel(QObject *parent = nullptr);

    enum SongRoles {
        FilePathRole = Qt::UserRole + 1,
        TitleRole,
        ArtistRole,
        AlbumRole,
        FeaturingArtistsRole,
        NumberInAlbumRole,
        AlbumArtistsRole,
        SongObjectRole,
        VisibleInQueueRole

    };

    void addSong(std::shared_ptr<Song> song);
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    int getLen() const;
    std::shared_ptr<Song> getSongAtIndex(int index);
    QList<std::shared_ptr<QueueEntry>> getQueue();
    void removeFromQueue(int songID);
    void insertAtIndex(int index, std::shared_ptr<Song> song);
    void insertAtIndex(int index, QList<std::shared_ptr<Song>> songs);
    void appendToQueue(std::shared_ptr<Song> song);
    void appendToQueue(QList<std::shared_ptr<Song>>);

    void pushFront(std::shared_ptr<QueueEntry> entry);
    void setQueue(QList<std::shared_ptr<QueueEntry>> queue_entries);
    std::shared_ptr<QueueEntry> popEntry(int index);
    void moveSong(int from, int to);
    void shuffleSongs();



signals:
    void decrementAlbum(QString &albumName, QStringList &albumArtists);
    void removeFromPlaylist(int songID);
    void removeCurrentPlaying(QString &path);


private:
    QList<std::shared_ptr<QueueEntry>> m_queue;
    int queueID;

};



#endif // QUEUEMODEL_H
