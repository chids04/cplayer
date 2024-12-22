#ifndef QUEUEMODEL_H
#define QUEUEMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "song.h"

class QueueModel : public QAbstractListModel
{
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
        SongObjectRole

    };

    void addSong(std::shared_ptr<Song> song);
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString getSongTitle(const QString &filePath) const;
    QString getSongArtist(const QString &filePath) const;
    QString getSongAlbum(const QString &filePath) const;
    QStringList getSongFeatures(const QString &filePath) const;
    int getSongTrackNum(const QString &filePath) const;
    QList<std::shared_ptr<Song>> getSongs();
    void removeSong(const QString &filePath);
    void addToQueue(QVector<std::shared_ptr<Song>> queue_songs);


signals:
    void decrementAlbum(QString &albumName, QStringList &albumArtists);
    void removeFromPlaylist(int songID);
    void removeCurrentPlaying(QString &path);


public slots:
    void onSongAdded(std::shared_ptr<Song> song);
    void removeFolderSongs(QString &folderPath);

private:
    QList<std::shared_ptr<Song>> m_songs;

};

#endif // QUEUEMODEL_H
