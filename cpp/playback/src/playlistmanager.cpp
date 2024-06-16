#include "playlistmanager.h"

PlaylistManager::PlaylistManager(AlbumHolder *albumHolder, SongListModel *songListModel, QObject *parent) : albumHolder(albumHolder),
    songListModel(songListModel), QObject(parent) {

    //creating now playing playlist

    playlists.push_back(Playlist(1, "Now Playing", songListModel));
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
    currentPlaylistID = 1; //id of now playing playlist

    playlists[0].clearPlaylist();

    QStringList songs = albumHolder->getSongsInAlbum(albumArtists, albumName);

    //need to sort the songs in album by album number
    //std::sort(songs.begin(), songs.end(), compareTrackNum);

    std::sort(songs.begin(), songs.end(), [this](const QString &url1, const QString &url2){
            return this->songListModel->getSongTrackNum(url1) < this->songListModel->getSongTrackNum(url2);
        });

    for(const QString &song : songs){
        playlists[0].addSong(song);
        qDebug() << song;
    }

    emit playlistQueued();
}

bool PlaylistManager::compareTrackNum(QString &url1,QString &url2){
    return songListModel->getSongTrackNum(url1) < songListModel->getSongTrackNum(url2);
}
