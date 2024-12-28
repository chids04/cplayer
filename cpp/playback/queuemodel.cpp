#include "queuemodel.h"

#include <QSettings>

QueueModel::QueueModel(QObject *parent)
    : QAbstractListModel{parent}
{
    QSettings settings;
    settings.beginGroup("nowPlaying");

    queueID = settings.value("lastQueueID", 0).toInt();
}

void QueueModel::addToQueue(QVector<std::shared_ptr<Song>> queue_songs)
{
    beginResetModel();
    for (const auto &song : queue_songs) {
        auto entry = std::make_shared<QueueEntry>();
        entry->song = song;
        entry->songID = song->id;
        m_queue.append(entry);
    }
    endResetModel();
}


void QueueModel::setQueue(QList<std::shared_ptr<QueueEntry> > queue_entries)
{
    beginResetModel();
    m_queue = queue_entries;
    endResetModel();
}

std::shared_ptr<QueueEntry> QueueModel::popEntry(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    auto removed_song = m_queue.takeAt(index);
    endRemoveRows();

    return removed_song;
}

void QueueModel::addSong(std::shared_ptr<Song> song) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    auto entry = std::make_shared<QueueEntry>();
    entry->song = song;
    entry->songID = song->id;
    m_queue << entry;
    endInsertRows();
}

void QueueModel::clear()
{
    if (!m_queue.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, m_queue.count() - 1);
        m_queue.clear();
        endRemoveRows();
    }
}

int QueueModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_queue.count();
}

QModelIndex QueueModel::index(int row, int column, const QModelIndex &parent) const {
    Q_UNUSED(parent)

    if (row >= 0 && row < rowCount() && column == 0) {
        return createIndex(row, column);
    } else {
        return QModelIndex();
    }
}

QVariant QueueModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_queue.count())
        return QVariant();

    auto entry = m_queue[index.row()];

    switch (role) {
    case FilePathRole:
        return entry->song->filePath;

    case TitleRole:
        return entry->song->title;

    case ArtistRole:
        return entry->song->artist;

    case AlbumRole:
        return entry->song->album;

    case FeaturingArtistsRole:
        return entry->song->featuringArtists;

    case NumberInAlbumRole:
        return entry->song->trackNum;

    case AlbumArtistsRole:
        return entry->song->albumArtists;

    case SongObjectRole:
        return QVariant::fromValue(entry->song);

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> QueueModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "filePath";
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[FeaturingArtistsRole] = "features";
    roles[NumberInAlbumRole] = "albumNum";
    roles[AlbumArtistsRole] = "albumArtists";
    roles[SongObjectRole] = "songObject";

    return roles;
}

int QueueModel::getLen() const
{
    return m_queue.size();
}

std::shared_ptr<Song> QueueModel::getSongAtIndex(int index)
{
    if (index >= m_queue.size() || index < 0) {
        return nullptr;
    } else {
        return m_queue.at(index)->song;
    }
}

QString QueueModel::getSongTitle(const QString &filePath) const
{
    for (const auto &entry : m_queue) {
        if (entry->song->filePath == filePath) {
            return entry->song->title;
        }
    }

    return QString();
}

QString QueueModel::getSongArtist(const QString &filePath) const
{
    for (const auto &entry : m_queue) {
        if (entry->song->filePath == filePath) {
            return entry->song->artist;
        }
    }

    return QString();
}

QString QueueModel::getSongAlbum(const QString &filePath) const
{
    for (const auto &entry : m_queue) {
        if (entry->song->filePath == filePath) {
            return entry->song->album;
        }
    }

    return QString();
}

QStringList QueueModel::getSongFeatures(const QString &filePath) const
{
    for (const auto &entry : m_queue) {
        if (entry->song->filePath == filePath) {
            return entry->song->featuringArtists;
        }
    }

    return QStringList();
}

int QueueModel::getSongTrackNum(const QString &filePath) const
{
    for (const auto &entry : m_queue) {
        if (entry->song->filePath == filePath) {
            return entry->song->trackNum;
        }
    }

    return 0;
}

QList<std::shared_ptr<QueueEntry>> QueueModel::getQueue()
{
    return m_queue;
}

int QueueModel::getLastQueueID()
{
    return queueID;
}

void QueueModel::insertAtIndex(int index, std::shared_ptr<Song> song)
{
    if (index > rowCount()) {
        index = rowCount();
    }

    beginInsertRows(QModelIndex(), index, index);
    auto entry = std::make_shared<QueueEntry>();
    entry->song = song;
    entry->songID = song->id;
    m_queue.push_front(entry);
    endInsertRows();
}

void QueueModel::pushFront(std::shared_ptr<QueueEntry> entry)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_queue.push_front(entry);
    endInsertRows();
}

void QueueModel::onSongAdded(std::shared_ptr<Song> song)
{
    addSong(song);
}

void QueueModel::moveSong(int from, int to)
{
    if (from < 0 || from >= rowCount() || to < 0 || to >= rowCount()) {
        return;
    }

    int adjustedTo = (from < to) ? to + 1 : to;

    beginMoveRows(QModelIndex(), from, from, QModelIndex(), adjustedTo);
    qDebug() << "moving" << m_queue.at(from)->song->title << "at index" << from
             << "to index" << to << m_queue.at(to)->song->title;

    m_queue.move(from, to);
    endMoveRows();
}
