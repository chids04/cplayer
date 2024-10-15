#include "playlistfilter.h"
#include "songlistmodel.h"

PlaylistFilter::PlaylistFilter(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(&SongListModel::instance());
}

PlaylistFilter &PlaylistFilter::instance()
{
    static PlaylistFilter playlistFilter;
    return playlistFilter;
}


QList<int> PlaylistFilter::filterList() const
{
    return m_filterList;
}

void PlaylistFilter::setFilterList(const QList<int> &newFilterList)
{
    if (m_filterList == newFilterList)
        return;
    m_filterList = newFilterList;
    invalidate();
    emit filterListChanged();
    qDebug() << "filter set";
}

bool PlaylistFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    int songID = sourceModel()->data(index, SongListModel::SongObjectRole).value<std::shared_ptr<Song>>()->id;
    qDebug() << songID << m_filterList;
    if(m_filterList.contains(songID)){
        return true;
    }

    return false;
}
