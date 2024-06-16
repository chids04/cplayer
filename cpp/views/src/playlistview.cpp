#include "playlistview.h"

PlaylistView::PlaylistView(PlaylistModel *playlistModel, SongListModel *songListModel, QObject *parent) : playlistModel(playlistModel), songListModel(songListModel)
{}

void PlaylistView::addPlaylist(QString playlistName, bool hasCover)
{
    Playlist playlist(playlistNum, playlistName, songListModel);
    playlistModel->addPlaylist(playlist);

    playlistNum++;
}

void PlaylistView::loadPlaylistSongs(int id)
{
    qDebug() << id;
    QModelIndex index = playlistModel->getIndexForID(id);
    QVariant idVariant = playlistModel->data(index, PlaylistModel::PlaylistIDRole);
    QVariant nameVariant = playlistModel->data(index, PlaylistModel::PlaylistNameRole);
    QVariant modelVariant = playlistModel->data(index, PlaylistModel::SongModelRole);
    QVariant hasCoverVariant = playlistModel->data(index, PlaylistModel::HasCoverRole);

    PlaylistSongsModel *playlistSongModel = modelVariant.value<PlaylistSongsModel*>();

    setPlaylistID(idVariant.toInt());
    setPlaylistName(nameVariant.toString());
    setHasCover(hasCoverVariant.toBool());
    setPlaylistSongsModel(playlistSongModel);
}

PlaylistSongsModel *PlaylistView::playlistSongsModel()
{
    qDebug() << "attempting to get model";
    return m_playlistSongsModel;
}


void PlaylistView::setPlaylistSongsModel(PlaylistSongsModel *newPlaylistSongsModel)
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

void PlaylistView::addSongToPlaylist(int id, int songIndex)
{
    QModelIndex index = playlistModel->getIndexForID(id);
    QVariant modelVariant = playlistModel->data(index, PlaylistModel::SongModelRole);
    PlaylistSongsModel *songModel = modelVariant.value<PlaylistSongsModel*>();

    songModel->addSong(songIndex);
    index = songModel->index(0);
    QVariant dataVariant = songModel->data(index, PlaylistSongsModel::TitleRole);
    QString songTitle = dataVariant.toString();

    qDebug() << "added" << songTitle << "to playlist" << id;

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
