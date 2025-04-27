#include "scplaylist.h"

#include <QThread>
#include <pybind11/pybind11.h>

SCPlaylist::SCPlaylist(QObject *parent)
    : QAbstractListModel{parent}
{}

int SCPlaylist::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return static_cast<int>(m_results.size());
}

QVariant SCPlaylist::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_results.size()))
        return QVariant();

    const SoundcloudItem &item = m_results[index.row()];

    switch (role) {
    case Qt::DisplayRole:
    case TitleRole:
        return QString::fromStdString(item.title);

    case ArtistRole:
        return QString::fromStdString(item.artist);

    case TypeRole:
        return QString::fromStdString(item.type);

    case UrlRole:
        return QString::fromStdString(item.permalink_url);

    case ArtworkUrlRole:
        return QString::fromStdString(item.artwork_url);

    case DurationRole:
        return formatDuration(item.duration);

    case DownloadableRole:
        return item.downloadable;

    case TrackCountRole:
        return item.track_count;
    
    case PlaylistSongsRole:
        return QVariant::fromValue(item.playlist_tracks);
    }

    return QVariant();
}

QHash<int, QByteArray> SCPlaylist::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[TypeRole] = "itemType";
    roles[UrlRole] = "url";
    roles[ArtworkUrlRole] = "artworkUrl";
    roles[DurationRole] = "duration";
    roles[DownloadableRole] = "downloadable";
    roles[TrackCountRole] = "trackCount";
    return roles;
}


const SoundcloudItem& SCPlaylist::getItem(int index) const
{
    return m_results[index];
}

void SCPlaylist::setSongs(std::vector<SoundcloudItem> results) {
    beginResetModel();
    m_results = results;
    endResetModel();
}

QString SCPlaylist::formatDuration(int64_t milliseconds) const
{
    int seconds = milliseconds / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    return QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QLatin1Char('0'));
}
