#ifndef SONGFILTERPROXYMODEL_H
#define SONGFILTERPROXYMODEL_H

#include <QString>
#include <QSortFilterProxyModel>

#include "songlistmodel.h"

class SongFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ANONYMOUS
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged)

public:
    explicit SongFilterProxyModel(SongListModel *songListModel, QObject *parent = nullptr);
    //static SongFilterProxyModel &instance();

    QString filterString() const;
    void setFilterString(const QString &filterString);

public slots:
    void refreshFilter() { invalidate(); }

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QString normalizeString(const QString &string) const;

    double computeMatchScore(const QStringList &tokens,
        const QString &title,
        const QString &artist,
        const QString &album) const;
signals:
    void filterStringChanged();
private:
    QString m_filterString;
};

Q_DECLARE_METATYPE(SongFilterProxyModel)
#endif // SONGFILTERPROXYMODEL_H
