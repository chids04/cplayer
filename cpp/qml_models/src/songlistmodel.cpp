#include "songlistmodel.h"

#include <QDebug>

#include "folderview.h"
#include "albumlistmodel.h"

SongListModel::SongListModel(QObject *parent) : QAbstractListModel(parent) {
    connect(this, &SongListModel::deleteAlbum, &AlbumListModel::instance(), &AlbumListModel::deleteAlbum);
}

SongListModel &SongListModel::instance()
{
    static SongListModel songListModel;
    return songListModel;
}

void SongListModel::addSong(std::shared_ptr<Song> song){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs << song;
    endInsertRows();
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

        case AlbumArtistsRole:
            return song->albumArtists;

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
    roles[SongObjectRole] = "songObject";

    return roles;
}

QString SongListModel::getSongTitle(const QString &filePath) const
{
    //add error checking here
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->title;
        }
    }

    return QString();
}

QString SongListModel::getSongArtist(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->artist;
        }
    }

    return QString();
}

QString SongListModel::getSongAlbum(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->album;
        }
    }

    return QString();
}

QStringList SongListModel::getSongFeatures(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->featuringArtists;
        }
    }

    return QStringList();
}

int SongListModel::getSongTrackNum(const QString &filePath) const
{
    for(const auto &song : m_songs){
        if(song->filePath == filePath){
            return song->trackNum;
        }
    }

    return 0;
}

QList<std::shared_ptr<Song> > SongListModel::getSongs()
{
    return m_songs;
}

void SongListModel::removeFolderSongs(QString &folderPath)
{
    QString songPath;

    for (int i = m_songs.size() - 1; i >= 0; --i) {
        songPath = m_songs[i]->filePath;
        if (songPath.contains(folderPath, Qt::CaseSensitive)) {
            emit deleteAlbum(m_songs[i]->album, m_songs[i]->albumArtists);
            beginRemoveRows(QModelIndex(), i, i);
            m_songs.removeAt(i);  // Remove song if its path contains the folderPath
            endRemoveRows();

        }
    }
}

void SongListModel::onSongAdded(std::shared_ptr<Song> song)
{
    addSong(song);
}
