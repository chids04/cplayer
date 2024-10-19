#ifndef ALBUMSEARCHFILTER_H
#define ALBUMSEARCHFILTER_H

#include <QSortFilterProxyModel>

class AlbumSearchFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)

public:
    explicit AlbumSearchFilter(QObject *parent = nullptr);
    static AlbumSearchFilter &instance();

    QString filterString() const;

    void setFilterString(const QString &newFilterString);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QString normalizeString(const QString &string) const;

signals:
    void filterStringChanged();

private:
    QString m_filterString;
};
#endif // ALBUMSEARCHFILTER_H
