#include "nowplaying.h"

#include "albumlistmodel.h"
#include "songlistmodel.h"

NowPlaying::NowPlaying(QObject *parent) :
    QObject(parent)
{
    QueueModel *queue_model = new QueueModel;
    QueueModelFilter *queue_proxy = new QueueModelFilter(queue_model);
    setQueueModel(queue_model);
    setQueueProxyModel(queue_proxy);
}

NowPlaying &NowPlaying::instance()
{
    static NowPlaying nowPlaying;
    return nowPlaying;
}

QList<std::shared_ptr<QueueEntry> > NowPlaying::getPlayedSongs()
{
    return m_playedSongs;
}

QList<std::shared_ptr<QueueEntry> > NowPlaying::getNowPlaying()
{
    return m_queueModel->getQueue();

}

void NowPlaying::loadFromSettings()
{
    QSettings settings;
    settings.beginGroup("nowPlaying");

    qint64 position = settings.value("nowPlayingSongPosition", 0).toLongLong();

    QList<int> queue_IDs   = settings.value("queue").value<QList<int>>();
    QList<int> played_IDs  = settings.value("queueHistory").value<QList<int>>();

    const auto allSongs = SongListModel::instance().getSongs();
    QHash<int, std::shared_ptr<Song>> song_map;
    for (const auto &s : allSongs) {
        song_map[s->id] = s;
    }

    QList<std::shared_ptr<QueueEntry>> queue_entries;
    for (int songID : queue_IDs) {
        if (!song_map.contains(songID)) {
            qWarning() << "Song with ID" << songID << "not found. Skipping.";
            continue;
        }
        auto entry = std::make_shared<QueueEntry>();
        entry->songID = songID;
        entry->song   = song_map[songID];
        queue_entries << entry;
    }

    QList<std::shared_ptr<QueueEntry>> played_entries;
    for (int songID : played_IDs) {
        if (!song_map.contains(songID)) {
            qWarning() << "Song with ID" << songID << "not found. Skipping.";
            continue;
        }
        auto entry = std::make_shared<QueueEntry>();
        entry->songID = songID;
        entry->song   = song_map[songID];
        played_entries << entry;
    }

    m_queueModel->setQueue(queue_entries);
    m_playedSongs = played_entries;

    settings.endGroup();

    if (!queue_entries.isEmpty()) {
        emit positionLoaded(position);
        emit songLoaded(m_queueModel->getSongAtIndex(0));
    }
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
        m_queueModel->addToQueue(songs);
    }
    else if(m_queueModel->getLen() == 0){
        //songQueue.append(songs);
        m_queueModel->addToQueue(songs);
        emit playSong(m_queueModel->getSongAtIndex(0));
    }
    else{
        //int index = currentIndex + 1;
        int index = 1;
        for(const auto &song : songs){
            //songQueue.insert(index, song);
            m_queueModel->insertAtIndex(index, song);
            index++;
        }
//        currentIndex++;
//        emit playSong(songQueue[currentIndex]);
        onNextClicked();
    }



}

void NowPlaying::playPlaylist(const Playlist &playlist, bool queue)
{
    QList<int> songIDs = playlist.getSongIDs();

    if(songIDs.count() == 0){
        return;
    }


    QList<std::shared_ptr<Song>> songs = SongListModel::instance().getSongs();

    //int insertIndex = currentIndex + 1;
    int insertIndex = 1;
    int numSongs = m_queueModel->getLen();

    for(const auto &song: songs){
        if(songIDs.contains(song->id)){
            if(queue){
                //songQueue.append(song);
                m_queueModel->addSong(song);
            }
            else if(numSongs == 0){
                //songQueue.append(song);
                m_queueModel->addSong(song);
            }
            else{
                //songQueue.insert(insertIndex, song);
                m_queueModel->insertAtIndex(insertIndex, song);
                insertIndex++;
            }

        }
    }


    if(!queue || m_queueModel->getLen() == 0){
        if(m_queueModel->getLen() == 0){
            playingSong = m_queueModel->popEntry(0);
            emit playSong(playingSong->song);
        }
        else{
            m_playedSongs.push_back(m_queueModel->popEntry(0));
            playingSong = m_queueModel->popEntry(0);
            emit playSong(playingSong->song);
        }
    }
}

void NowPlaying::onPreviousClicked(int duration)
{
    if(m_playedSongs.size() == 0 || duration >= 3000){
        emit playSong(playingSong->song);
    }
    else{
        auto prev_song = m_playedSongs.takeLast();
        m_queueModel->pushFront(playingSong);
        playingSong = prev_song;
        emit playSong(playingSong->song);
    }
}

void NowPlaying::onNextClicked()
{
    if(m_queueModel->getLen() == 0){
        emit jumpToEnd();
        return;
    }
    else{
        if(playingSong == nullptr){
            return;
        }

        m_playedSongs.push_back(playingSong);

        //limit size of history, reduce mem usage
        if(m_playedSongs.size() > 100){
            m_playedSongs.pop_front();
        }

        playingSong = m_queueModel->popEntry(0);
        emit playSong(playingSong->song);
    }
}

void NowPlaying::queueNext(std::shared_ptr<Song> song)
{

    if(m_queueModel->getLen() == 0) {
        m_queueModel->addSong(song);
    }
    else{
        m_queueModel->insertAtIndex(1, song);
    }
}

void NowPlaying::addToQueue(std::shared_ptr<Song> song)
{
    m_queueModel->addSong(song);
}

void NowPlaying::playNow(std::shared_ptr<Song> song)
{

    if(m_queueModel->getLen() == 0){
        //too lazy to make queue entry obj lol
        m_queueModel->insertAtIndex(0, song);
        playingSong = m_queueModel->popEntry(0);
        emit playSong(playingSong->song);
        m_playedSongs.push_back(playingSong);

    }
    else{
        if(playingSong != nullptr){
            m_playedSongs.push_back(playingSong);
        }

        m_queueModel->insertAtIndex(0, song);
        playingSong = m_queueModel->popEntry(0);
        emit playSong(playingSong->song);
        m_playedSongs.push_back(playingSong);
    }

}

void NowPlaying::moveSong(int from, int to)
{
    m_queueModel->moveSong(from, to);
}

QueueModel *NowPlaying::queueModel() const
{
    return m_queueModel;
}

void NowPlaying::setQueueModel(QueueModel *newQueueModel)
{
    if (m_queueModel == newQueueModel)
        return;
    m_queueModel = newQueueModel;
    emit queueModelChanged();
}


QueueModelFilter *NowPlaying::queueProxyModel() const
{
    return m_queueProxyModel;
}

void NowPlaying::setQueueProxyModel(QueueModelFilter *newQueueProxyModel)
{
    if (m_queueProxyModel == newQueueProxyModel)
        return;
    m_queueProxyModel = newQueueProxyModel;
    emit queueProxyModelChanged();
}
