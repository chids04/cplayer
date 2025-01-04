#ifndef SONGLISTMODEL_H
#define SONGLISTMODEL_H

#include <QtQml>
#include <QAbstractListModel>


#include <memory>

#include "song.h"

class SongListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SongListModel(QObject *parent = nullptr);
    static SongListModel &instance();

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

signals:
    void decrementAlbum(QString &albumName, QStringList &albumArtists);
    void removeFromPlaylist(int songID);
    void removeCurrentPlaying(QString &path);
    void removeFromNowPlaying(int songID);


public slots:
    void onSongAdded(std::shared_ptr<Song> song);
    void removeFolderSongs(QString &folderPath);

private:
    QList<std::shared_ptr<Song>> m_songs;
    static SongListModel *modelInstance;

};

#endif // SONGLISTMODEL_H
