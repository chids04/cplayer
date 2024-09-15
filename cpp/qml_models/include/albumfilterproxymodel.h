#ifndef ALBUMFILTERPROXYMODEL_H
#define ALBUMFILTERPROXYMODEL_H

#include <QString>
#include <QSortFilterProxyModel>

#include "songlistmodel.h"

class AlbumFilterProxyModel : public QSortFilterProxyModel
{

    Q_OBJECT
    Q_PROPERTY(QString currentAlbumName READ currentAlbumName WRITE setCurrentAlbumName NOTIFY currentAlbumNameChanged)

public:
    explicit AlbumFilterProxyModel(QObject *parent = nullptr);
    static AlbumFilterProxyModel &instance();

    QString currentAlbumName() const;

public slots:
    void setCurrentAlbumName(const QString &newAlbumName);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;


signals:
    void currentAlbumNameChanged();
private:
    QString m_currentAlbumName;
};

#endif // ALBUMFILTERPROXYMODEL_H
