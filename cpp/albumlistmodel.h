#ifndef ALBUMLISTMODEL_H
#define ALBUMLISTMODEL_H

#include <QList>
#include <QString>
#include <QAbstractListModel>

#include "album.h"
class AlbumListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AlbumListModel(QObject *parent = nullptr);

    enum AlbumRoles {
        AlbumNameRole = Qt::UserRole + 1,
        AlbumGenreRole,
        AlbumSongsRole,
        AlbumArtistRole,
        AlbumYearRole,
        AlbumSongCountRole

    };

    void addAlbum(const Album &album);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Album> m_albums;
};


#endif // ALBUMLISTMODEL_H
