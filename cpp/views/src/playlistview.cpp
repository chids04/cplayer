#include "playlistview.h"

PlaylistView::PlaylistView(PlaylistModel *playlistModel, QObject *parent) : playlistModel(playlistModel)
{}

void PlaylistView::addPlaylist(QString playlistName, bool hasCover)
{
    Playlist playlist(playlistNum, playlistName);
    playlistModel->addPlaylist(playlist);

    playlistNum++;
}

void PlaylistView::loadPlaylistSongs(int id)
{
    QModelIndex index = playlistModel->getIndexForID(id);
    QVariant idVariant = playlistModel->data(index, PlaylistModel::PlaylistIDRole);
    QVariant nameVariant = playlistModel->data(index, PlaylistModel::PlaylistNameRole);
    QVariant modelVariant = playlistModel->data(index, PlaylistModel::SongModelRole);
    QVariant hasCoverVariant = playlistModel->data(index, PlaylistModel::HasCoverRole);

    setPlaylistID(idVariant.toInt());
    setPlaylistName(nameVariant.toString());
    setHasCover(hasCoverVariant.toBool());
    setPlaylistSongsModel(modelVariant);
}

QVariant PlaylistView::playlistSongsModel() const
{
    return m_playlistSongsModel;
}


void PlaylistView::setPlaylistSongsModel(const QVariant &newPlaylistSongsModel)
{
    if (m_playlistSongsModel == newPlaylistSongsModel)
        return;
    m_playlistSongsModel = newPlaylistSongsModel;
    emit playlistSongsModelChanged();
}

QString PlaylistView::playlistName() const
{
    return m_playlistName;
}

void PlaylistView::setPlaylistName(const QString &newPlaylistName)
{
    if (m_playlistName == newPlaylistName)
        return;
    m_playlistName = newPlaylistName;
    emit playlistNameChanged();
}

void PlaylistView::addSongToPlaylist(int id, QString filePath, QString title, QString artist, QString album, QStringList featuringArtists, int length, int trackNum)
{
    QModelIndex index = playlistModel->getIndexForID(id);
    QVariant modelVariant = playlistModel->data(index, PlaylistModel::SongModelRole);
    PlaylistSongsModel *songModel = modelVariant.value<PlaylistSongsModel*>();

    songModel->addSong(filePath, title, artist, album, featuringArtists, length, trackNum);

}

bool PlaylistView::hasCover() const
{
    return m_hasCover;
}

void PlaylistView::setHasCover(bool newHasCover)
{
    if (m_hasCover == newHasCover)
        return;
    m_hasCover = newHasCover;
    emit hasCoverChanged();
}

int PlaylistView::playlistID() const
{
    return m_playlistID;
}

void PlaylistView::setPlaylistID(int newPlaylistID)
{
    if (m_playlistID == newPlaylistID)
        return;
    m_playlistID = newPlaylistID;
    emit playlistIDChanged();
}
