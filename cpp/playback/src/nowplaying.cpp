#include "nowplaying.h"

#include "albumlistmodel.h"
#include "songlistmodel.h"
#include "mediaplayercontroller.h"

#include <iostream>

NowPlaying::NowPlaying(QObject *parent) :
    QObject(parent)
{
}

NowPlaying &NowPlaying::instance()
{
    static NowPlaying nowPlaying;
    return nowPlaying;
}

QList<std::shared_ptr<Song> > NowPlaying::getNowPlaying()
{
    return songQueue;
}

int NowPlaying::getCurrentIndex()
{
    return currentIndex;
}

void NowPlaying::loadFromSettings()
{
    QSettings settings;
    currentIndex = settings.value("nowPlayingCurrentIndex", 0).toInt();
    qint64 position = settings.value("nowPlayingSongPosition", 0).toLongLong();
    QList<int> songIDs = settings.value("nowPlayingList").value<QList<int>>();

    //no songs
    if(songIDs.isEmpty()){
        return;
    }

    for (const auto &song : SongListModel::instance().getSongs()){
        if(songIDs.contains(song->id)){
            songQueue.append(song);
        }
    }

    int len = songQueue.length();

    if (currentIndex < 0 || currentIndex >= len) {
        // Invalid index or empty queue, reset to a safe state
        currentIndex = 0; // or handle as necessary
    }

    if(len == 0){
        return;
    }


    emit songLoaded(songQueue[currentIndex]);
    //emit positionLoaded(position);
}


void NowPlaying::playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue)
{
    QModelIndex albumIndex = AlbumListModel::instance().findAlbumIndex(albumName, albumArtists);
    QVariant albumSongsVariant = AlbumListModel::instance().data(albumIndex, AlbumListModel::AlbumSongsRole);
    QList<std::shared_ptr<Song>> songs = albumSongsVariant.value<QList<std::shared_ptr<Song>>>();

    std::sort(songs.begin(), songs.end(), [](const std::shared_ptr<Song> &a, const std::shared_ptr<Song> &b){
        return a->trackNum < b->trackNum;
    });


    if(queue){
        songQueue.append(songs);
    }

    else if(songQueue.count() == 0){
        songQueue.append(songs);
        emit playSong(songQueue[currentIndex]);
    }

    else{
        int index = currentIndex + 1;
        for(const auto &song : songs){
            songQueue.insert(index, song);
            index++;
        }
        currentIndex++;

        emit playSong(songQueue[currentIndex]);
    }



}

void NowPlaying::playPlaylist(Playlist playlist, bool queue)
{
    QList<int> songIDs = playlist.getSongIDs();
    QList<std::shared_ptr<Song>> songs = SongListModel::instance().getSongs();

    int insertIndex = currentIndex + 1;
    int numSongs = songQueue.count();

    for(const auto &song: songs){
        if(songIDs.contains(song->id)){
            if(queue){
                songQueue.append(song);
            }
            else if(numSongs == 0){
                songQueue.append(song);
            }
            else{
                songQueue.insert(insertIndex, song);
                insertIndex++;
            }
        }
    }

    if(!queue){
        currentIndex++;
        emit playSong(songQueue[currentIndex]);
    }
    else if(numSongs == 0){
        emit playSong(songQueue[currentIndex]);
    }
}

void NowPlaying::onPreviousClicked(int duration)
{
    if(currentIndex - 1 == -1 && songQueue.count() != 0) {
        emit playSong(songQueue[0]);
    }
    else if(songQueue.count() != 0){
        if(duration >= 3000){
            emit playSong(songQueue[currentIndex]);
        }
        else{
            currentIndex--;
            emit playSong(songQueue[currentIndex]);
        }
    }
}

void NowPlaying::onNextClicked()
{
    if(currentIndex + 1 == songQueue.count()){
        emit jumpToEnd();
    }

    else if(songQueue.count() != 0){
        currentIndex++;
        emit playSong(songQueue[currentIndex]);
    }

}

void NowPlaying::queueNext(std::shared_ptr<Song> song)
{
    if(songQueue.count() == 0) {
        songQueue.append(song);
    }
    else{
        songQueue.insert(currentIndex + 1, song);
    }
}

void NowPlaying::addToQueue(std::shared_ptr<Song> song)
{
    songQueue.append(song);
}

void NowPlaying::playNow(std::shared_ptr<Song> song)
{
    if(songQueue.count() == 0){
        songQueue.append(song);
        emit playSong(songQueue[currentIndex]);
    }

    else{
        songQueue.insert(currentIndex + 1, song);
        currentIndex++;
        emit playSong(songQueue[currentIndex]);
    }

}





