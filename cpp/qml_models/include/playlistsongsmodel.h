#ifndef PLAYLISTSONGSMODEL_H
#define PLAYLISTSONGSMODEL_H

#include <QString>
#include <QAbstractListModel>

#include "song.h"
#include "songlistmodel.h"

class PlaylistSongsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlaylistSongsModel(SongListModel *songListModel, QObject *parent = nullptr);

    enum SongRoles {
        FilePathRole = Qt::UserRole + 1,
        TitleRole,
        ArtistRole,
        AlbumRole,
        FeaturingArtistsRole,
        NumberInAlbumRole,
        SongObjectRole

    };

    void addSong(int index);
    void clear();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column=0, const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<std::shared_ptr<Song>> m_songs;
    SongListModel *songListModel;
};

Q_DECLARE_METATYPE(PlaylistSongsModel*)
#endif // PLAYLISTSONGSMODEL_H
