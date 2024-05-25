#ifndef ALBUMFILTERPROXYMODEL_H
#define ALBUMFILTERPROXYMODEL_H

#include <QString>
#include <QSortFilterProxyModel>

#include "songlistmodel.h"

class AlbumFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString albumName READ albumName WRITE setAlbumName NOTIFY albumNameChanged)
public:
    explicit AlbumFilterProxyModel(QObject *parent = nullptr);


    QString albumName() const;

public slots:
    void setAlbumName(const QString &newAlbumName);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

signals:
    void albumNameChanged();
private:
    QString m_albumName;
};

#endif // ALBUMFILTERPROXYMODEL_H
