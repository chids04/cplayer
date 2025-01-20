#include <QSettings>

#include "playlistmodel.h"
#include "playlistmanager.h"

PlaylistModel::PlaylistModel(PlaylistManager *playlistManager, QObject *parent) : QAbstractListModel(parent),
    playlistManager(playlistManager)
{

}


void PlaylistModel::addPlaylist(std::shared_ptr<Playlist> playlist)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_playlists << playlist;
    endInsertRows();

}

void PlaylistModel::removePlaylist(int playlistID)
{
    for (int row = 0; row < m_playlists.count(); ++row) {
        if (m_playlists[row]->getID() == playlistID) {
            beginRemoveRows(QModelIndex(), row, row);
            m_playlists.removeAt(row);
            endRemoveRows();
            return;
        }
    }
}

QList<std::shared_ptr<Playlist> > PlaylistModel::getPlaylists()
{
    return m_playlists;
}

void PlaylistModel::loadPlaylists(QList<std::shared_ptr<Playlist>> playlists)
{
    beginResetModel();
    m_playlists = playlists;
    endResetModel();
}

void PlaylistModel::modifyPlaylist(int id, const QString &name, bool hasCover)
{
    for(auto &playlist: m_playlists){
        if(playlist->getID() == id){
            playlist->setName(name);
            playlist->setHasCover(hasCover);
            break;
        }

    }

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

    auto &playlist = m_playlists[index.row()];

    switch(role){
        case PlaylistIDRole:
            return playlist->getID();

        case PlaylistNameRole:
            return playlist->getPlaylistName();

        case SongCountRole:
            return playlist->getSongCount();

        case DurationRole:
            return playlist->getDuration();

        case HasCoverRole:
            return playlist->playlistHasCover();

        case PlaylistObjRole:
            return QVariant::fromValue(playlist);

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
    roles[HasCoverRole] = "playlistHasCover";
    roles[PlaylistObjRole] = "playlistObject";

    return roles;
}

void PlaylistModel::removeSongs(int songID)
{
    //pretty ineffcient rn, will optimise later if needed
    for(auto &playlist : m_playlists){
        playlist->removeSong(songID);
    }
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
        if (m_playlists[row]->getID() == id) {
            return index(row, 0);
        }
    }
    return QModelIndex();
}


void PlaylistModel::readPlaylists()
{
    QSettings settings;
    QList<Playlist> loadedPlaylists = settings.value("playlists").value<QList<Playlist>>();
    int playlistNum = settings.value("playlistNum", 0).toInt();


    for(const Playlist &playlist : loadedPlaylists){
        std::shared_ptr<Playlist> playlistPtr = std::make_shared<Playlist>(playlist);
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_playlists.append(playlistPtr);
        qDebug() << "appendednewplaylist";
        endInsertRows();
    }

    playlistManager->loadPlaylistNum(playlistNum);
}

void PlaylistModel::savePlaylists()
{
    //saves playlists and the playlistNum, since playlistNum is used as the id, this prevents duplicate playlists ids;
    QSettings settings;
    int playlistNum = playlistManager->getPlaylistNum();
    QList<Playlist> playlistObj;

    for(const auto &playlist : m_playlists){
        playlistObj.append(*playlist);
    }

    settings.setValue("playlists", QVariant::fromValue(playlistObj));
    settings.setValue("playlistNum", playlistNum);
}

void PlaylistModel::resetModel()
{
    beginResetModel();
    endResetModel();
}

