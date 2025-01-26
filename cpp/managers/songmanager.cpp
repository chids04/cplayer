#include "songmanager.h"


SongManager::SongManager(PlaybackManager *playbackManager, QObject *parent)
{
    //load songlistmodel from settings here
    //load albums from settings
    albumListModel = new AlbumListModel;

    songListModel = new SongListModel(albumListModel, playbackManager->mediaPlayer(), playbackManager->nowPlaying());

    mediaPlayer = playbackManager->mediaPlayer();

    //these models exposed to qml
    SongFilterProxyModel *songFilterProxyModel = new SongFilterProxyModel(songListModel);
    AlbumFilterProxyModel *albumFilterProxyModel = new AlbumFilterProxyModel(songListModel);
    AlbumSearchFilter *albumSearchFilter = new AlbumSearchFilter(albumListModel);

    setSongModel(songFilterProxyModel);
    setAlbumSongsModel(albumFilterProxyModel);
    setAlbumSearchModel(albumSearchFilter);

    setFeaturesList(new QStringListModel);
    setAlbumArtistsList(new QStringListModel);

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

void SongManager::insertFeature(const QString &feature)
{
    if(m_featuresList->insertRow(m_featuresList->rowCount())){
        QModelIndex index = m_featuresList->index(m_featuresList->rowCount() - 1);
        m_featuresList->setData(index, feature);
    }
}

void SongManager::setFeaturesToEdit(const QStringList &features)
{
    m_featuresList->setStringList(features);
}

void SongManager::insertArtist(const QString &artist)
{
    if(m_albumArtistsList->insertRow(m_albumArtistsList->rowCount())){
        QModelIndex index = m_albumArtistsList->index(m_albumArtistsList->rowCount() - 1);
        m_albumArtistsList->setData(index, artist);
    }
}

void SongManager::setAlbumArtistsToEdit(const QStringList &albumArtists)
{
    m_albumArtistsList->setStringList(albumArtists);
}


void SongManager::saveChanges(Song* song, const QString &title, const QString &leadingArtist, const QString &album,
                              const QString &genre, int year, int trackNum,
                              bool hasCover, const QUrl &coverPath)
{
    song->m_trackNum = trackNum;
    song->m_title = title;
    song->m_artist = leadingArtist;
    song->m_album = album;
    song->m_featuringArtists = m_featuresList->stringList();
    song->m_albumArtists = m_albumArtistsList->stringList();
    song->m_genre = genre;

    songListModel->updateSong(song->m_id);
    mediaPlayer->updateSong(song);
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

QStringListModel *SongManager::featuresList() const
{
    return m_featuresList;
}

void SongManager::setFeaturesList(QStringListModel *newFeaturesList)
{
    if (m_featuresList == newFeaturesList)
        return;
    m_featuresList = newFeaturesList;
    emit featuresListChanged();
}

QStringListModel *SongManager::albumArtistsList() const
{
    return m_albumArtistsList;
}

void SongManager::setAlbumArtistsList(QStringListModel *newAlbumArtistsList)
{
    if (m_albumArtistsList == newAlbumArtistsList)
        return;
    m_albumArtistsList = newAlbumArtistsList;
    emit albumAritstsListChanged();
}
