#ifndef SONGLISTMODEL_H
#define SONGLISTMODEL_H

#include <QAbstractListModel>

#include "song.h"

class SongListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SongListModel(QObject *parent = nullptr);

    enum SongRoles {
        FilePathRole = Qt::UserRole + 1,
        TitleRole,
        ArtistRole,
        AlbumRole,
        FeaturingArtistsRole

    };

    void addSong(const Song &song);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Song> m_songs;
};

#endif // SONGLISTMODEL_H
