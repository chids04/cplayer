#include "albumfilterproxymodel.h"

AlbumFilterProxyModel::AlbumFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setSourceModel(&SongListModel::instance());
}

AlbumFilterProxyModel &AlbumFilterProxyModel::instance()
{
    static AlbumFilterProxyModel albumFilterProxyModel;
    return albumFilterProxyModel;
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
    qDebug() << flag;
    return sourceModel()->data(index, SongListModel::AlbumRole).toString() == m_currentAlbumName;
}

//sorts the songs by album number
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
