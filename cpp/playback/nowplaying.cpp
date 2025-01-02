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

void NowPlaying::playFromQueue()
{
    playingSong = m_queueModel->popEntry(0);
    emit playSong(playingSong->song);
}

int NowPlaying::getCurrentSongID()
{
    if(playingSong != nullptr){
        return playingSong->songID;
    }

    return -1;
}

void NowPlaying::loadFromSettings()
{
    QSettings settings;
    settings.beginGroup("nowPlaying");

    qint64 position = settings.value("nowPlayingSongPosition", 0).toLongLong();

    QList<int> queue_IDs   = settings.value("queue").value<QList<int>>();
    QList<int> played_IDs  = settings.value("queueHistory").value<QList<int>>();
    int curr_song = settings.value("playingSong").toInt();

    const auto allSongs = SongListModel::instance().getSongs();
    QHash<int, std::shared_ptr<Song>> song_map;
    for (const auto &s : allSongs) {
        song_map[s->id] = s;

        if(s->id == curr_song){
            auto entry = std::make_shared<QueueEntry>();
            entry->songID = s->id;
            entry->song = s;
            playingSong = entry;
        }
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
        if(playingSong != nullptr){
            emit songLoaded(playingSong->song);
            emit positionLoaded(position);
        }
        else{
            //just get first item in queue
            playingSong = m_queueModel->popEntry(0);
            emit songLoaded(playingSong->song);
        }
    }
    else if(queue_entries.isEmpty() && playingSong != nullptr){
        emit positionLoaded(position);
        emit songLoaded(playingSong->song);
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

    if(queue == true){
        m_queueModel->appendToQueue(songs);
    }
    else{
        m_queueModel->insertAtIndex(0, songs);
        if(playingSong != nullptr){
            m_playedSongs.push_back(playingSong);
        }

        playingSong = m_queueModel->popEntry(0);
        emit playSong(playingSong->song);
    }


}

void NowPlaying::playPlaylist(const Playlist &playlist, bool queue)
{
    QList<int> songIDs = playlist.getSongIDs();

    if(songIDs.count() == 0){
        return;
    }


    QList<std::shared_ptr<Song>> songs = SongListModel::instance().getSongs();
    QList<std::shared_ptr<Song>> p_songs;

    for(const auto &song : songs){
        if(songIDs.contains(song->id)){
            p_songs << song;
        }
    }

    if(queue == true){
        m_queueModel->appendToQueue(p_songs);
    }

    else{
        m_queueModel->insertAtIndex(0, p_songs);

        if(playingSong != nullptr){
            m_playedSongs.push_back(playingSong);
        }

        playingSong = m_queueModel->popEntry(0);
        emit playSong(playingSong->song);
    }

}

void NowPlaying::onPreviousClicked(int duration)
{
    if(m_playedSongs.size() == 0 || duration >= 3000){
        if(playingSong == nullptr){
            return;
        }
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
    m_queueModel->insertAtIndex(0, song);
}

void NowPlaying::addToQueue(std::shared_ptr<Song> song)
{
    m_queueModel->appendToQueue(song);
}

void NowPlaying::playNow(std::shared_ptr<Song> song)
{
    m_queueModel->insertAtIndex(0, song);
    playingSong = m_queueModel->popEntry(0);
    qDebug() << "playing song" << playingSong->song->title;
    emit playSong(playingSong->song);
    m_playedSongs.push_back(playingSong);
}

void NowPlaying::moveSong(int from, int to)
{
    m_queueModel->moveSong(from, to);
}

void NowPlaying::clearQueue()
{
    m_queueModel->clear();
}

void NowPlaying::onRemoveFromNowPlaying(int songID)
{
    qDebug() << "removing" << songID << "from nowplaying";
    for(int i=0; i<m_playedSongs.size(); ++i) {
        if(m_playedSongs[i]->songID == songID){
            m_playedSongs.removeAt(i);
        }
    }

    if(playingSong != nullptr && playingSong->songID == songID){
        playingSong = nullptr;
    }

    m_queueModel->removeFromQueue(songID);


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
