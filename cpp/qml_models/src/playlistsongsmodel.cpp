#include "playlistsongsmodel.h"
#include <QDebug>

PlaylistSongsModel::PlaylistSongsModel(SongListModel *songListModel, QObject *parent) : songListModel(songListModel), QAbstractListModel(parent) {}

void PlaylistSongsModel::addSong(int index){

    QModelIndex idx = songListModel->index(index);
    QVariant songVariant = songListModel->data(idx, SongListModel::SongObjectRole);
    auto song = songVariant.value<std::shared_ptr<Song>>();

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();
}

void PlaylistSongsModel::clear()
{
    if(!m_songs.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_songs.count() - 1);
        m_songs.clear();
        endRemoveRows();
    }
}

int PlaylistSongsModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_songs.count();
}

QModelIndex PlaylistSongsModel::index(int row, int column, const QModelIndex &parent) const {
    Q_UNUSED(parent)

    // Check for a valid row and column
    if (row >= 0 && row < rowCount() && column == 0) {
        return createIndex(row, column);
    } else {
        return QModelIndex(); // Return an invalid index if out of bounds
    }
}

QVariant PlaylistSongsModel::data(const QModelIndex &index, int role) const {
    if(index.row() < 0 || index.row() >= m_songs.count())
        return QVariant();

    auto &song = m_songs[index.row()];
    switch(role){
    case FilePathRole:
        return song->filePath;

    case TitleRole:
        return song->title;

    case ArtistRole:
        return song->artist;

    case AlbumRole:
        return song->album;

    case FeaturingArtistsRole:
        return song->featuringArtists;

    case NumberInAlbumRole:
        return song->trackNum;

    case SongObjectRole:
        return QVariant::fromValue(song);

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PlaylistSongsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "filePath";
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[FeaturingArtistsRole] = "features";
    roles[NumberInAlbumRole] = "albumNum";
    roles[SongObjectRole] = "songObject";

    return roles;
}

