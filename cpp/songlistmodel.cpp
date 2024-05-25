#include "songlistmodel.h"
#include <QDebug>

SongListModel::SongListModel(QObject *parent) : QAbstractListModel(parent) {}

void SongListModel::addSong(const Song &song){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();
}

int SongListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_songs.count();
}

QVariant SongListModel::data(const QModelIndex &index, int role) const {
    if(index.row() < 0 || index.row() >= m_songs.count())
        return QVariant();

    const Song &song = m_songs[index.row()];
    switch(role){
        case FilePathRole:
            return song.filePath;

        case TitleRole:
            return song.title;

        case ArtistRole:
            return song.artist;

        case AlbumRole:
            return song.album;

        case FeaturingArtistsRole:
            return song.featuringArtists;

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> SongListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "filePath";
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[FeaturingArtistsRole] = "features";

    return roles;
}
