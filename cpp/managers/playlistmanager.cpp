#include "playlistmanager.h"

#include <QSettings>

#include "playlist.h"
#include "playlistmodel.h"
#include "playlistfilter.h"
#include "playlistimageprovider.h"

PlaylistManager::PlaylistManager(SongListModel *songListModel,
    PlaylistImageProvider *playlistImageProvider, QObject *parent)
    : playlistImageProvider(playlistImageProvider), QObject(parent)
{
    setPlaylistModel(new PlaylistModel(this));
    setPlaylistSongs(new PlaylistFilter(songListModel));
}


void PlaylistManager::addPlaylist(const QString &playlistName, int rotation, const QUrl &coverPath, bool hasCover)
{
    std::shared_ptr<Playlist> playlist = std::make_shared<Playlist>(playlistNum, playlistName, hasCover);
    m_playlistModel->addPlaylist(playlist);


    if(hasCover){
        playlistImageProvider->addCover(playlistNum, rotation, coverPath.toLocalFile());
    }

    playlistNum++;
}

void PlaylistManager::modifyPlaylist(int id, const QString &playlistName, int rotation, const QUrl &coverPath, bool hasCover)
{
    m_playlistModel->modifyPlaylist(id, playlistName, hasCover);

    if(hasCover){
        playlistImageProvider->addCover(id, rotation, coverPath.toLocalFile());
    }

    m_playlistModel->resetModel();

}

void PlaylistManager::removePlaylist(int playlistID)
{
    m_playlistModel->removePlaylist(playlistID);
    playlistImageProvider->removeCover(playlistID);
}

void PlaylistManager::loadPlaylistSongs(int id)
{
    QModelIndex index = m_playlistModel->getIndexForID(id);
    QVariant idVariant = m_playlistModel->data(index, PlaylistModel::PlaylistIDRole);
    QVariant nameVariant = m_playlistModel->data(index, PlaylistModel::PlaylistNameRole);
    QVariant hasCoverVariant = m_playlistModel->data(index, PlaylistModel::HasCoverRole);

    std::shared_ptr<Playlist> playlist = m_playlistModel->data(index, PlaylistModel::PlaylistObjRole).value<std::shared_ptr<Playlist>>();
    QList<int> songIDs = playlist->getSongIDs();

    setPlaylistID(idVariant.toInt());
    setPlaylistName(nameVariant.toString());
    setHasCover(hasCoverVariant.toBool());
    setCurrentPlaylist(*playlist);

    m_playlistSongs->setFilterList(songIDs);
}



void PlaylistManager::addSongToPlaylist(int id, std::shared_ptr<Song> song)
{
    QModelIndex index = m_playlistModel->getIndexForID(id);

    QVariant playlistObj = m_playlistModel->data(index, PlaylistModel::PlaylistObjRole);
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

void PlaylistManager::saveToSettings()
{
    m_playlistModel->savePlaylists();
    playlistImageProvider->saveCovers();

}

int PlaylistManager::getPlaylistNum()
{
    return playlistNum;
}

void PlaylistManager::loadPlaylistNum(int num)
{
    playlistNum = num;
}

void PlaylistManager::loadFromSettings()
{
    m_playlistModel->readPlaylists();
    playlistImageProvider->loadCovers();
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

PlaylistModel *PlaylistManager::playlistModel() const
{
    return m_playlistModel;
}

void PlaylistManager::setPlaylistModel(PlaylistModel *newPlaylistModel)
{
    if (m_playlistModel == newPlaylistModel)
        return;
    m_playlistModel = newPlaylistModel;
    emit playlistModelChanged();
}

PlaylistFilter *PlaylistManager::playlistSongs() const
{
    return m_playlistSongs;
}

void PlaylistManager::setPlaylistSongs(PlaylistFilter *newPlaylistSongs)
{
    if (m_playlistSongs == newPlaylistSongs)
        return;
    m_playlistSongs = newPlaylistSongs;
    emit playlistSongsChanged();
}

int PlaylistManager::songCount() const
{
    return m_songCount;
}

void PlaylistManager::setSongCount(int newSongCount)
{
    if (m_songCount == newSongCount)
        return;
    m_songCount = newSongCount;
    emit songCountChanged();
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
    emit songCountChanged();
}
