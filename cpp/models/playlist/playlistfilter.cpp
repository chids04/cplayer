#include "playlistfilter.h"
#include "songlistmodel.h"

PlaylistFilter::PlaylistFilter(SongListModel *songListModel, QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(songListModel);
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
}

bool PlaylistFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    int songID = sourceModel()->data(index, SongListModel::SongObjectRole).value<std::shared_ptr<Song>>()->id;
    if(m_filterList.contains(songID)){
        return true;
    }

    return false;
}
