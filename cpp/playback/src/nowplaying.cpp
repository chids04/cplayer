#include "nowplaying.h"

NowPlaying::NowPlaying(SongListModel *songListModel, AlbumListModel *albumListModel, QObject *parent) :
    QObject(parent), songListModel(songListModel), albumListModel(albumListModel)
{

}

void NowPlaying::playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue)
{
    QModelIndex albumIndex = albumListModel->findAlbumIndex(albumName, albumArtists);
    QVariant albumSongsVariant = albumListModel->data(albumIndex, AlbumListModel::AlbumSongsRole);
    QList<std::shared_ptr<Song>> songs = albumSongsVariant.value<QList<std::shared_ptr<Song>>>();

    if(queue){
        songQueue.append(songs);
    }
    else{
        int index = currentIndex + 1;
        for(const auto &song : songs){
            songQueue.insert(index, song);
            index++;
        }
    }

}

void NowPlaying::onPreviousClicked(int duration)
{
    if(currentIndex - 1 == -1) {
        emit playSong(songQueue[0]);
    }
    else{
        if(duration <= 4000){
            emit playSong(songQueue[currentIndex]);
        }
        else{
            emit playSong(songQueue[currentIndex-1]);
            currentIndex--;
        }
    }
}

void NowPlaying::onNextClicked()
{
    if(currentIndex + 1 == songQueue.count()){
        emit jumpToEnd();
    }
    else{
        emit playSong(songQueue[currentIndex + 1]);
    }
}

void NowPlaying::addToQueue(QString filePath)
{

}


