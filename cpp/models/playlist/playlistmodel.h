#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>

#include "playlist.h"

class PlaylistManager;

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlaylistModel(PlaylistManager *playlistManager, QObject *parent = nullptr);

    enum PlaylistRole {
        PlaylistIDRole = Qt::UserRole + 1,
        PlaylistNameRole,
        SongCountRole,
        DurationRole,
        HasCoverRole,
        PlaylistObjRole
    };

    void addPlaylist(std::shared_ptr<Playlist>);
    void removePlaylist(int playlistID);
    void clear();
    QList<std::shared_ptr<Playlist>> getPlaylists();
    void loadPlaylists(QList<std::shared_ptr<Playlist>> playlists);
    void modifyPlaylist(int id, const QString &name, bool hasCover);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column=0, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex getIndexForID(int id) const;
    QHash<int, QByteArray> roleNames() const override;
    void readPlaylists();
    void savePlaylists();
    void resetModel();

public slots:
    void removeSongs(int songID);

private:
    QList<std::shared_ptr<Playlist>> m_playlists;
    PlaylistManager *playlistManager;
    QList<int> toRemove;
};

Q_DECLARE_METATYPE(PlaylistModel*)
#endif // PLAYLISTMODEL_H


