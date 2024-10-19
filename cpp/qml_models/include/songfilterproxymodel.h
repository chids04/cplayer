#ifndef SONGFILTERPROXYMODEL_H
#define SONGFILTERPROXYMODEL_H

#include <QString>
#include <QSortFilterProxyModel>

class SongFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)

public:
    explicit SongFilterProxyModel(QObject *parent = nullptr);
    static SongFilterProxyModel &instance();

    QString filterString() const;
    void setFilterString(const QString &filterString);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QString normalizeString(const QString &string) const;
    int matchScore(const QString &text, const QString &query) const;

signals:
    void filterStringChanged();

private:
    QString m_filterString;
};

#endif // SONGFILTERPROXYMODEL_H
