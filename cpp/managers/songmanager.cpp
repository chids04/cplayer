#include "songmanager.h"


SongManager::SongManager(PlaybackManager *playbackManager, QObject *parent)
{
    //load songlistmodel from settings here
    //load albums from settings
    albumListModel = new AlbumListModel;

    songListModel = new SongListModel(albumListModel, playbackManager->mediaPlayer(), playbackManager->nowPlaying());

    //these models exposed to qml
    SongFilterProxyModel *songFilterProxyModel = new SongFilterProxyModel(songListModel);
    AlbumFilterProxyModel *albumFilterProxyModel = new AlbumFilterProxyModel(songListModel);
    AlbumSearchFilter *albumSearchFilter = new AlbumSearchFilter(albumListModel);

    setSongModel(songFilterProxyModel);
    setAlbumSongsModel(albumFilterProxyModel);
    setAlbumSearchModel(albumSearchFilter);

}

void SongManager::initPlaylists(PlaylistManager *playlistManager)
{
    //avoids circular dependency
    connect(songListModel, &SongListModel::removeFromPlaylist, playlistManager->playlistModel(), &PlaylistModel::removeSongs);
}

void SongManager::loadFromSettings()
{
    songListModel->readSongs();
}

void SongManager::saveToSettings()
{
    songListModel->saveSongs();
}

SongFilterProxyModel *SongManager::songModel() const
{
    return m_songModel;
}

void SongManager::setSongModel(SongFilterProxyModel *newSongModel)
{
    if (m_songModel == newSongModel)
        return;
    m_songModel = newSongModel;
    emit songModelChanged();
}

AlbumFilterProxyModel *SongManager::albumSongsModel() const
{
    return m_albumSongsModel;
}

void SongManager::setAlbumSongsModel(AlbumFilterProxyModel *newAlbumSongsModel)
{
    if (m_albumSongsModel == newAlbumSongsModel)
        return;
    m_albumSongsModel = newAlbumSongsModel;
    emit albumSongsModelChanged();
}

AlbumSearchFilter *SongManager::albumSearchModel() const
{
    return m_albumSearchModel;
}

void SongManager::setAlbumSearchModel(AlbumSearchFilter *newAlbumSearchModel)
{
    if (m_albumSearchModel == newAlbumSearchModel)
        return;
    m_albumSearchModel = newAlbumSearchModel;
    emit albumSearchModelChanged();
}

Album SongManager::currentAlbum() const
{
    return m_currentAlbum;
}


void SongManager::setCurrentAlbum(const Album &newCurrentAlbum)
{
    m_currentAlbum = newCurrentAlbum;
    emit currentAlbumChanged();
}

SongListModel *SongManager::getSongListModel() const
{
    return songListModel;
}

AlbumListModel *SongManager::getAlbumListModel() const
{
    return albumListModel;
}

void SongManager::setAlbum(const Album &album)
{
    setCurrentAlbum(album);
    setAlbumName(album.getName());
    setAlbumArtists(album.getArtist());
    setAlbumYear(album.getYear());
    setAlbumGenre(album.getGenre());

    m_albumSongsModel->setCurrentAlbumName(album.getName());
}

QString SongManager::albumName() const
{
    return m_albumName;
}

void SongManager::setAlbumName(const QString &newAlbumName)
{
    if (m_albumName == newAlbumName)
        return;
    m_albumName = newAlbumName;
    emit albumNameChanged();
}

QStringList SongManager::albumAritsts() const
{
    return m_albumArtists;
}

void SongManager::setAlbumArtists(const QStringList &newAlbumArtists)
{
    if (m_albumArtists == newAlbumArtists)
        return;
    m_albumArtists = newAlbumArtists;
    emit albumArtistsChanged();
}

QString SongManager::albumGenre() const
{
    return m_albumGenre;
}

void SongManager::setAlbumGenre(const QString &newAlbumGenre)
{
    if (m_albumGenre == newAlbumGenre)
        return;
    m_albumGenre = newAlbumGenre;
    emit albumGenreChanged();
}

int SongManager::albumYear() const
{
    return m_albumYear;
}

void SongManager::setAlbumYear(int newAlbumYear)
{
    if (m_albumYear == newAlbumYear)
        return;
    m_albumYear = newAlbumYear;
    emit albumYearChanged();
}
