#include "playlistmanager.h"

#include "playlist.h"
#include "playlistmodel.h"

PlaylistManager::PlaylistManager(QObject *parent) : QObject(parent)
{
    //
}

PlaylistManager &PlaylistManager::instance()
{
    static PlaylistManager playlistManager;
    return playlistManager;
}


void PlaylistManager::addPlaylist(QString playlistName, bool hasCover)
{
    Playlist playlist(playlistNum, playlistName, hasCover);
    PlaylistModel::instance().addPlaylist(playlist);

    playlistNum++;
}

void PlaylistManager::loadPlaylistSongs(int id)
{
    QModelIndex index = PlaylistModel::instance().getIndexForID(id);
    QVariant idVariant = PlaylistModel::instance().data(index, PlaylistModel::PlaylistIDRole);
    QVariant nameVariant = PlaylistModel::instance().data(index, PlaylistModel::PlaylistNameRole);
    QVariant modelVariant = PlaylistModel::instance().data(index, PlaylistModel::SongModelRole);
    QVariant hasCoverVariant = PlaylistModel::instance().data(index, PlaylistModel::HasCoverRole);

    PlaylistSongsModel *playlistSongModel = modelVariant.value<PlaylistSongsModel*>();

    setPlaylistID(idVariant.toInt());
    setPlaylistName(nameVariant.toString());
    setHasCover(hasCoverVariant.toBool());

    //moved playlistsongs model to modelhandler.h
    setPlaylistSongsModel(playlistSongModel);
    //ModelHandler::instance().setPlaylistSongsList(playlistSongModel);
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
    QVariant modelVariant = PlaylistModel::instance().data(index, PlaylistModel::SongModelRole);
    PlaylistSongsModel *songModel = modelVariant.value<PlaylistSongsModel*>();

    songModel->addSong(song);

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
