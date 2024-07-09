#ifndef SONGFILTERPROXYMODEL_H
#define SONGFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class SongFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)

public:
    explicit SongFilterProxyModel(QObject *parent = nullptr);

    QString filterString() const;
    void setFilterString(const QString &filterString);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

signals:
    void filterStringChanged();

private:
    QString m_filterString;
};

#endif // SONGFILTERPROXYMODEL_H
