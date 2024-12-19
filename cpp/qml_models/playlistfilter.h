#ifndef PLAYLISTFILTER_H
#define PLAYLISTFILTER_H

#include <QString>
#include <QSortFilterProxyModel>

class PlaylistFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QList<int> filterList READ filterList WRITE setFilterList NOTIFY filterListChanged)

public:
    explicit PlaylistFilter(QObject *parent = nullptr);
    static PlaylistFilter &instance();


    QList<int> filterList() const;
    void setFilterList(const QList<int> &newFilterList);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

signals:
    void filterListChanged();

private:
    QList<int> m_filterList;
};
#endif // PLAYLISTFILTER_H
