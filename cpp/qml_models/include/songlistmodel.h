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
        FeaturingArtistsRole,
        NumberInAlbumRole

    };

    void addSong(const Song &song);
    void clear();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QString getSongTitle(const QString &filePath) const;
    QString getSongArtist(const QString &filePath) const;
    QString getSongAlbum(const QString &filePath) const;
    QStringList getSongFeatures(const QString &filePath) const;
    int getSongTrackNum(const QString &filePath) const;


private:
    QList<Song> m_songs;
};

#endif // SONGLISTMODEL_H
