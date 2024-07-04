#ifndef ALBUMLISTMODEL_H
#define ALBUMLISTMODEL_H

#include <QList>
#include <QString>
#include <QAbstractListModel>

#include <memory>

#include "album.h"
#include "song.h"

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
    QModelIndex findAlbumIndex(const QString &albumName, const QStringList &albumArtits);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void clear();

public slots:
    void updateAlbum(std::shared_ptr<Song> song);

private:
    QList<Album> m_albums;
};


#endif // ALBUMLISTMODEL_H
