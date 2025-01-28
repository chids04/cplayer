#include "songlistmodel.h"

#include <QDebug>


SongListModel::SongListModel(AlbumListModel *albumListModel, MediaPlayerController *mediaPlayerController, NowPlaying *nowPlaying,
                           QObject *parent) : QAbstractListModel(parent) {

    connect(this, &SongListModel::decrementAlbum, albumListModel, &AlbumListModel::decrementAlbum);
    connect(this, &SongListModel::updateAlbum, albumListModel, &AlbumListModel::updateAlbum);
    connect(this, &SongListModel::removeCurrentPlaying, mediaPlayerController, &MediaPlayerController::onRemoveCurrentPlaying);
    connect(this, &SongListModel::removeFromNowPlaying, nowPlaying, &NowPlaying::onRemoveFromNowPlaying);

}


void SongListModel::addSong(Song* song){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();

    emit updateAlbum(song);
}

void SongListModel::clear()
{
    if(!m_songs.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_songs.count() - 1);
        m_songs.clear();
        endRemoveRows();
    }
}

int SongListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_songs.count();
}

QModelIndex SongListModel::index(int row, int column, const QModelIndex &parent) const {
    Q_UNUSED(parent)

    // Check for a valid row and column
    if (row >= 0 && row < rowCount() && column == 0) {
        return createIndex(row, column);
    } else {
        return QModelIndex(); // Return an invalid index if out of bounds
    }
}

QVariant SongListModel::data(const QModelIndex &index, int role) const {
    if(index.row() < 0 || index.row() >= m_songs.count())
        return QVariant();

    auto song = m_songs[index.row()];

    switch(role){
        case FilePathRole:
        return song->m_filePath;

        case TitleRole:
        return song->m_title;

        case ArtistRole:
        return song->m_artist;

        case AlbumRole:
        return song->m_album;

        case FeaturingArtistsRole:
        return song->m_featuringArtists;

        case NumberInAlbumRole:
        return song->m_trackNum;

        case AlbumArtistsRole:
            return song->m_albumArtists;

        case SongObjectRole:
            return QVariant::fromValue(song);

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
    roles[NumberInAlbumRole] = "albumNum";
    roles[AlbumArtistsRole] = "albumArtists";
    roles[SongObjectRole] = "songObj";

    return roles;
}

void SongListModel::updateSong(int id)
{
    int index = -1;
    for (int i = 0; i < m_songs.size(); ++i) {
        if (m_songs[i]->m_id == id) {
            index = i;
        }
    }

    QModelIndex modelIndex = createIndex(index, 0);
    emit dataChanged(modelIndex, modelIndex);
}


QList<Song* > SongListModel::getSongs()
{
    return m_songs;
}

void SongListModel::removeSong(const QString &filePath)
{
    for(int i=m_songs.size() - 1; i>= 0; --i){
        if(m_songs[i]->m_filePath == filePath){
            emit decrementAlbum(m_songs[i]->m_album, m_songs[i]->m_albumArtists);
            emit removeFromPlaylist(m_songs[i]->m_id);
            emit removeCurrentPlaying(m_songs[i]->m_filePath);
            emit removeFromNowPlaying(m_songs[i]->m_id);

            beginRemoveRows(QModelIndex(), i, i);
            m_songs.removeAt(i);
            endRemoveRows();

            return;
        }
    }
}

void SongListModel::removeFolderSongs(const QString &folderPath)
{
    QString songPath;

    for (int i = m_songs.size() - 1; i >= 0; --i) {
        songPath = m_songs[i]->m_filePath;
        if (songPath.contains(folderPath, Qt::CaseSensitive)) {
            emit decrementAlbum(m_songs[i]->m_album, m_songs[i]->m_albumArtists);
            emit removeFromPlaylist(m_songs[i]->m_id);
            emit removeCurrentPlaying(m_songs[i]->m_filePath);
            emit removeFromNowPlaying(m_songs[i]->m_id);

            beginRemoveRows(QModelIndex(), i, i);
            m_songs.removeAt(i);  // Remove song if its path contains the folderPath
            endRemoveRows();

        }
    }
}

void SongListModel::onSongAdded(Song* song)
{
    addSong(song);
}

void SongListModel::readSongs()
{
    QSettings settings;
    QList<SongData> songDataList = settings.value("songs").value<QList<SongData>>();

    for (const SongData &songData : songDataList) {
        Song* songPtr = new Song();
        songPtr->fromSongData(songData);

        addSong(songPtr);
    }
}

void SongListModel::saveSongs()
{
    QSettings settings;
    QList<SongData> songDataList;

    for (const auto &song : m_songs) {
        songDataList.append(song->toSongData());
    }

    settings.setValue("songs", QVariant::fromValue(songDataList));
}
