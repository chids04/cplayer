#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>

#include "playlist.h"

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlaylistModel(QObject *parent = nullptr);

    enum PlaylistRole {
        PlaylistIDRole = Qt::UserRole + 1,
        PlaylistNameRole,
        SongCountRole,
        DurationRole,
        SongModelRole,
        HasCoverRole
    };

    void addPlaylist(const Playlist &playlist);
    void clear();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column=0, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex getIndexForID(int id) const;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Playlist> m_playlists;
};

Q_DECLARE_METATYPE(PlaylistModel*)
#endif // PLAYLISTMODEL_H


