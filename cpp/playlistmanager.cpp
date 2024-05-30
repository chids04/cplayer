#include "playlistmanager.h"

PlaylistManager::PlaylistManager(AlbumHolder *albumHolder, QObject *parent) : albumHolder(albumHolder), QObject(parent) {

    //creating now playing playlist

    playlists.push_back(Playlist(1));
}

QString PlaylistManager::setNextFilePath() const
{
    return m_nextFilePath;
}

void PlaylistManager::nextFilePath(const QString &newNextFilePath)
{
    if (m_nextFilePath == newNextFilePath)
        return;
    m_nextFilePath = newNextFilePath;
    emit onNextFilePathChanged();
}

QString PlaylistManager::nextTrackTitle() const
{
    return m_nextTrackTitle;
}

QString PlaylistManager::nextLeadingArtist() const
{
    return m_nextLeadingArtist;
}

QStringList PlaylistManager::features() const
{
    return m_features;
}

void PlaylistManager::setFeatures(const QStringList &newFeatures)
{
    if (m_features == newFeatures)
        return;
    m_features = newFeatures;
    emit featuresChanged();
}

QString PlaylistManager::getNextSong()
{
    for(Playlist &playlist: playlists){
        if(playlist.getID() == currentPlaylistID){
            return playlist.getNextSong();
        }
    }

    return QString();
}

QString PlaylistManager::getPreviousSong()
{
    for(Playlist &playlist: playlists){
        if(playlist.getID() == currentPlaylistID){
            return playlist.getPreviousSong();
        }
    }

    return QString();
}

void PlaylistManager::playAlbum(const QString &albumName, const QStringList &albumArtists)
{
    //album gets added to now playing list (first playlist in the list)
    currentPlaylistID = 1;

    playlists[0].clearPlaylist();

    QStringList songs = albumHolder->getSongsInAlbum(albumArtists, albumName);
    for(const QString &song : songs){
        playlists[0].addSong(song);
        qDebug() << song;
    }

    emit playlistQueued();


}
