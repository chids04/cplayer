#include "albumfilterproxymodel.h"

#include "songlistmodel.h"

AlbumFilterProxyModel::AlbumFilterProxyModel(SongListModel *songListModel, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setSourceModel(songListModel);
    sort(0, Qt::AscendingOrder);
}


void AlbumFilterProxyModel::setCurrentAlbumName(const QString &newAlbumName)
{
    if (m_currentAlbumName == newAlbumName)
        return;
    m_currentAlbumName = newAlbumName;
    invalidateFilter();
    emit currentAlbumNameChanged();
}

bool AlbumFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    bool flag = sourceModel()->data(index, SongListModel::AlbumRole).toString() == m_currentAlbumName ? true: false;
    return sourceModel()->data(index, SongListModel::AlbumRole).toString() == m_currentAlbumName;
}

bool AlbumFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left, SongListModel::NumberInAlbumRole);
    QVariant rightData = sourceModel()->data(right, SongListModel::NumberInAlbumRole);

    return leftData.toInt() < rightData.toInt();
}

QString AlbumFilterProxyModel::currentAlbumName() const
{
    return m_currentAlbumName;
}
