#include "queuemodelfilter.h"


QueueModelFilter::QueueModelFilter(QueueModel *source_model, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setSourceModel(source_model);
    setDynamicSortFilter(false);
}

bool QueueModelFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    return sourceModel()->data(index, QueueModel::VisibleInQueueRole).toBool();
}


