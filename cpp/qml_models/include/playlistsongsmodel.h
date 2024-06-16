#ifndef PLAYLISTSONGSMODEL_H
#define PLAYLISTSONGSMODEL_H

#include <QString>
#include <QAbstractListModel>

#include "song.h"

class PlaylistSongsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlaylistSongsModel(QObject *parent = nullptr);

    enum SongRoles {
        FilePathRole = Qt::UserRole + 1,
        TitleRole,
        ArtistRole,
        AlbumRole,
        FeaturingArtistsRole,
        NumberInAlbumRole

    };

    void addSong(QString filePath, QString title, QString artist, QString album, QStringList featuringArtists, int length, int trackNum);
    void clear();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Song> m_songs;
};

#endif // PLAYLISTSONGSMODEL_H
