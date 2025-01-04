#ifndef QUEUEMODELFILTER_H
#define QUEUEMODELFILTER_H

#include <QSortFilterProxyModel>
#include <QObject>

#include "queuemodel.h"

class QueueModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit QueueModelFilter(QueueModel *source_model, QObject *parent = nullptr);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // QUEUEMODELFILTER_H
