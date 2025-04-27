#include <QRandomGenerator>

#include "nowplaying.h"
#include "albumlistmodel.h"
#include "songlistmodel.h"
#include "songmanager.h"
#include "mediaplayercontroller.h"

NowPlaying::NowPlaying(MediaPlayerController *mediaPlayerController, QObject *parent) :
    QObject(parent), m_mediaPlayer(mediaPlayerController)
{
    QueueModel *queue_model = new QueueModel;
    QueueModelFilter *queue_proxy = new QueueModelFilter(queue_model);
    setQueueModel(queue_model);
    setQueueProxyModel(queue_proxy);
}

void NowPlaying::saveNowPlaying()
{
    //only need to store song id
    QList<std::shared_ptr<QueueEntry>> queue = m_queueModel->getQueue();
    int curr_song_id = getCurrentSongID();

    qint64 position = m_mediaPlayer->position();

    QList<int> queue_IDs;
    QList<int> played_IDs;

    for(auto &queue_entry : queue){
        queue_IDs << queue_entry->songID;
    }

    for(auto &played_entry : m_playedSongs){
        played_IDs << played_entry->songID;
    }

    QSettings settings;
    settings.beginGroup("nowPlaying");

    settings.setValue("queue", QVariant::fromValue(queue_IDs));
    settings.setValue("queueHistory", QVariant::fromValue(played_IDs));
    settings.setValue("playingSong", curr_song_id);
    settings.setValue("nowPlayingSongPosition", QVariant::fromValue(position));
    settings.setValue("isShuffle", QVariant::fromValue(m_shuffle));
    settings.setValue("isLoop", QVariant::fromValue(m_loop));

    settings.endGroup();
}


void NowPlaying::loadFromSettings()
{
    QSettings settings;
    settings.beginGroup("nowPlaying");

    qint64 position = settings.value("nowPlayingSongPosition", 0).toLongLong();
    bool isShuffle = settings.value("isShuffle", false).toBool();
    bool isLoop = settings.value("isLoop", false).toBool();
    setShuffle(isShuffle);
    setLoop(isLoop);

    QList<int> queue_IDs   = settings.value("queue").value<QList<int>>();
    QList<int> played_IDs  = settings.value("queueHistory").value<QList<int>>();
    int curr_song = settings.value("playingSong").toInt();

    const auto allSongs = m_songListModel->getSongs();
    QHash<int, Song*> song_map;
    for (const auto &s : allSongs) {
        song_map[s->m_id] = s;

        if(s->m_id == curr_song){
            auto entry = std::make_shared<QueueEntry>();
            entry->songID = s->m_id;
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

void NowPlaying::setModels(SongManager *songManager)
{
    m_songListModel = songManager->getSongListModel();
    m_albumListModel = songManager->getAlbumListModel();
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




void NowPlaying::playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue)
{
    QModelIndex albumIndex = m_albumListModel->findAlbumIndex(albumName, albumArtists);
    QVariant albumSongsVariant = m_albumListModel->data(albumIndex, AlbumListModel::AlbumSongsRole);
    QList<Song*> songs = albumSongsVariant.value<QList<Song*>>();

    std::sort(songs.begin(), songs.end(), [](const Song* a, const Song* b){
        return a->m_trackNum < b->m_trackNum;
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


    QList<Song*> songs = m_songListModel->getSongs();
    QList<Song*> p_songs;

    for(const auto &song : songs){
        if(songIDs.contains(song->m_id)){
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
        if(m_playedSongs.size() > 0){ 
            //add all the songs in played songs to queue
            if(m_loop == true){
                for(const auto &entry: m_playedSongs){
                    m_queueModel->appendToQueue(entry->song);
                }

                playingSong = m_queueModel->popEntry(0);
                emit playSong(playingSong->song);
            }
        }

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

void NowPlaying::queueNext(Song* song)
{
    m_queueModel->insertAtIndex(0, song);
}

void NowPlaying::addToQueue(Song* song)
{
    m_queueModel->appendToQueue(song);
}

void NowPlaying::playNow(Song* song)
{

    m_queueModel->insertAtIndex(0, song);
    playingSong = m_queueModel->popEntry(0);
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

void NowPlaying::onCheckQueue()
{
    if(m_queueModel->getLen() == 0) {
        return;
    }
    else{
        playingSong = m_queueModel->popEntry(0);
        emit playSong(playingSong->song);
    }
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

bool NowPlaying::shuffle() const
{
    return m_shuffle;
}

bool NowPlaying::loop() const
{
    return m_loop;
}

void NowPlaying::setShuffle(bool newShuffle)
{
    if (m_shuffle == newShuffle)
        return;
    m_shuffle = newShuffle;

    if(m_shuffle == true){
        m_queueModel->shuffleSongs();
    }

    emit shuffleChanged();
}

void NowPlaying::setLoop(bool newLoop)
{
    if(m_loop == newLoop){
        return;
    }
    m_loop = newLoop;

    emit loopChanged();
}
