#include "albumfilterproxymodel.h"

AlbumFilterProxyModel::AlbumFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

void AlbumFilterProxyModel::setAlbumName(const QString &newAlbumName)
{
    if (m_albumName == newAlbumName)
        return;
    m_albumName = newAlbumName;
    invalidateFilter();
    emit albumNameChanged();
}

bool AlbumFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    bool flag = sourceModel()->data(index, SongListModel::AlbumRole).toString() == m_albumName ? true: false;
    qDebug() << flag;
    return sourceModel()->data(index, SongListModel::AlbumRole).toString() == m_albumName;
}

//sorts the songs by album number
bool AlbumFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right)
{
    QVariant leftData = sourceModel()->data(left, SongListModel::NumberInAlbumRole);
    QVariant rightData = sourceModel()->data(right, SongListModel::NumberInAlbumRole);

    return leftData.toInt() < rightData.toInt();
}

QString AlbumFilterProxyModel::albumName() const
{
    return m_albumName;
}
