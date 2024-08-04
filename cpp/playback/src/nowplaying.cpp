#include "nowplaying.h"

NowPlaying::NowPlaying(QObject *parent) :
    QObject(parent)
{}

NowPlaying &NowPlaying::instance()
{
    static NowPlaying nowPlaying;
    return nowPlaying;
}

NowPlaying *NowPlaying::create(QQmlEngine *engine, QJSEngine *)
{
    return &NowPlaying::instance();
}


void NowPlaying::playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue)
{
    qDebug() << "playing album" << albumName << "by" << albumArtists;
    QModelIndex albumIndex = AlbumListModel::instance().findAlbumIndex(albumName, albumArtists);
    QVariant albumSongsVariant = AlbumListModel::instance().data(albumIndex, AlbumListModel::AlbumSongsRole);
    QList<std::shared_ptr<Song>> songs = albumSongsVariant.value<QList<std::shared_ptr<Song>>>();

    std::sort(songs.begin(), songs.end(), [](const std::shared_ptr<Song> &a, const std::shared_ptr<Song> &b){
        return a->trackNum < b->trackNum;
    });

    qDebug() << "got list of songs in album";

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





