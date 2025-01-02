#include "playlistmanager.h"

#include <QSettings>

#include "playlist.h"
#include "playlistmodel.h"
#include "playlistfilter.h"
#include "playlistimageprovider.h"

PlaylistManager::PlaylistManager(QObject *parent) : QObject(parent)
{
}

PlaylistManager &PlaylistManager::instance()
{
    static PlaylistManager playlistManager;
    return playlistManager;
}


void PlaylistManager::addPlaylist(QString playlistName, QUrl coverPath, bool hasCover)
{
    std::shared_ptr<Playlist> playlist = std::make_shared<Playlist>(playlistNum, playlistName, hasCover);
    PlaylistModel::instance().addPlaylist(playlist);

    if(hasCover){
        playlistImageProvider->addCover(playlistNum, coverPath.toLocalFile());
    }

    playlistNum++;
}

void PlaylistManager::removePlaylist(int playlistID)
{
    PlaylistModel::instance().removePlaylist(playlistID);
    playlistImageProvider->removeCover(playlistID);
}

void PlaylistManager::loadPlaylistSongs(int id)
{
    QModelIndex index = PlaylistModel::instance().getIndexForID(id);
    QVariant idVariant = PlaylistModel::instance().data(index, PlaylistModel::PlaylistIDRole);
    QVariant nameVariant = PlaylistModel::instance().data(index, PlaylistModel::PlaylistNameRole);
    QVariant hasCoverVariant = PlaylistModel::instance().data(index, PlaylistModel::HasCoverRole);

    std::shared_ptr<Playlist> playlist = PlaylistModel::instance().data(index, PlaylistModel::PlaylistObjRole).value<std::shared_ptr<Playlist>>();
    QList<int> songIDs = playlist->getSongIDs();

    setPlaylistID(idVariant.toInt());
    setPlaylistName(nameVariant.toString());
    setHasCover(hasCoverVariant.toBool());
    setCurrentPlaylist(*playlist);

    PlaylistFilter::instance().setFilterList(songIDs);
}

PlaylistSongsModel *PlaylistManager::playlistSongsModel()
{
    return m_playlistSongsModel;
}


void PlaylistManager::setPlaylistSongsModel(PlaylistSongsModel *newPlaylistSongsModel)
{
    if (m_playlistSongsModel == newPlaylistSongsModel)
        return;
    m_playlistSongsModel = newPlaylistSongsModel;
    emit playlistSongsModelChanged();
}

QString PlaylistManager::playlistName() const
{
    return m_playlistName;
}

void PlaylistManager::setPlaylistName(const QString &newPlaylistName)
{
    if (m_playlistName == newPlaylistName)
        return;
    m_playlistName = newPlaylistName;
    emit playlistNameChanged();
}

void PlaylistManager::addSongToPlaylist(int id, std::shared_ptr<Song> song)
{
    QModelIndex index = PlaylistModel::instance().getIndexForID(id);

    QVariant playlistObj = PlaylistModel::instance().data(index, PlaylistModel::PlaylistObjRole);
    std::shared_ptr<Playlist> playlist = playlistObj.value<std::shared_ptr<Playlist>>();

    playlist->addSong(song->id);
}

bool PlaylistManager::hasCover() const
{
    return m_hasCover;
}

void PlaylistManager::setHasCover(bool newHasCover)
{
    if (m_hasCover == newHasCover)
        return;
    m_hasCover = newHasCover;
    emit hasCoverChanged();
}

int PlaylistManager::playlistID() const
{
    return m_playlistID;
}

void PlaylistManager::setPlaylistID(int newPlaylistID)
{
    if (m_playlistID == newPlaylistID)
        return;
    m_playlistID = newPlaylistID;
    emit playlistIDChanged();
}

void PlaylistManager::savePlaylists()
{
    QSettings settings;

}

int PlaylistManager::getPlaylistNum()
{
    return playlistNum;
}

void PlaylistManager::loadPlaylistNum(int num)
{
    playlistNum = num;
}

Playlist PlaylistManager::currentPlaylist() const
{
    return m_currentPlaylist;
}

void PlaylistManager::setCurrentPlaylist(const Playlist &newCurrentPlaylist)
{
    if (m_currentPlaylist == newCurrentPlaylist)
        return;
    m_currentPlaylist = newCurrentPlaylist;
    emit currentPlaylistChanged();
}

void PlaylistManager::setPlaylistImageProvider(PlaylistImageProvider *imgProvider)
{
    playlistImageProvider = imgProvider;
}
