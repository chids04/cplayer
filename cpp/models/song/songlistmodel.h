#ifndef SONGLISTMODEL_H
#define SONGLISTMODEL_H

#include <QtQml>
#include <QAbstractListModel>


#include <memory>

#include "song.h"
#include "albumlistmodel.h"
#include "mediaplayercontroller.h"
#include "nowplaying.h"


class SongListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SongListModel(AlbumListModel *albumListModel, MediaPlayerController *mediaPlayerController,
                           NowPlaying *nowPlaying, QObject *parent = nullptr);

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
    void readSongs();
    void saveSongs();

signals:
    void decrementAlbum(const QString &albumName, const QStringList &albumArtists);
    void removeFromPlaylist(int songID);
    void removeCurrentPlaying(const QString &path);
    void removeFromNowPlaying(int songID);
    void updateAlbum(std::shared_ptr<Song>);


public slots:
    void onSongAdded(std::shared_ptr<Song> song);
    void removeFolderSongs(const QString &folderPath);

private:
    QList<std::shared_ptr<Song>> m_songs;
    static SongListModel *modelInstance;

};

#endif // SONGLISTMODEL_H
