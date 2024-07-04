#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent)
{
}

void PlaylistModel::addPlaylist(const Playlist &playlist)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_playlists << playlist;
    endInsertRows();

}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_playlists.count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_playlists.count())
        return QVariant();

    const Playlist &playlist = m_playlists[index.row()];

    switch(role){
        case PlaylistIDRole:
            return playlist.getID();

        case PlaylistNameRole:
            return playlist.getPlaylistName();

        case SongCountRole:
            return playlist.getSongCount();

        case DurationRole:
            return playlist.getDuration();

        case SongModelRole:
            return QVariant::fromValue(playlist.getSongModel());

        case HasCoverRole:
            return playlist.playlistHasCover();

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> PlaylistModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[PlaylistIDRole] = "playlistID";
    roles[PlaylistNameRole] = "playlistName";
    roles[SongCountRole] = "songCount";
    roles[DurationRole] = "duration";
    roles[SongModelRole] = "songModel";
    roles[HasCoverRole] = "playlistHasCover";

    return roles;
}

QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent) const {
    Q_UNUSED(parent)

    // Check for a valid row and column
    if (row >= 0 && row < rowCount() && column == 0) {
        return createIndex(row, column);
    } else {
        return QModelIndex(); // Return an invalid index if out of bounds
    }
}

QModelIndex PlaylistModel::getIndexForID(int id) const
{
    for (int row = 0; row < m_playlists.count(); ++row) {
        if (m_playlists[row].getID() == id) {
            return index(row, 0);
        }
    }
    return QModelIndex();
}

