#include "queue.h"

Queue::Queue(QString name, QList<std::shared_ptr<Song>> songs, QObject *parent) : QObject(parent), m_queueName(name),
    originalSongs(songs), shuffledSongs(songs)
{
    shuffleSongs();
}

QList<std::shared_ptr<Song>> Queue::getSongs()
{
    if(shuffle){
        return shuffledSongs;
    }
    else{
        return originalSongs;
    }

}

void Queue::shuffleSongs()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(shuffledSongs.begin(),  shuffledSongs.end(), g);
}

std::shared_ptr<Song> Queue::popSong()
{
    if (!originalSongs.isEmpty()) {
        auto song = originalSongs.takeFirst(); // Removes and returns the first song
        return song;
    }
    return nullptr;
}

QString Queue::queueName() const
{
    return m_queueName;
}

void Queue::queueName(const QString &newQueueName)
{
    if (m_queueName == newQueueName)
        return;
    m_queueName = newQueueName;
    emit queueNameChanged();
}
