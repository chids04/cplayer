#ifndef PLAYLISTSONGSMODEL_H
#define PLAYLISTSONGSMODEL_H

#include <QString>
#include <QAbstractListModel>

#include "song.h"

class PlaylistSongsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlaylistSongsModel(QObject *parent = nullptr);

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
    QModelIndex index(int row, int column=0, const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void removeFolderSongs(QString &folderPath);

private:
    QList<std::shared_ptr<Song>> m_songs;
};

Q_DECLARE_METATYPE(PlaylistSongsModel*)
#endif // PLAYLISTSONGSMODEL_H
