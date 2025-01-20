#ifndef SONGMANAGER_H
#define SONGMANAGER_H

#include <QObject>
#include "songlistmodel.h"
#include "playlistmanager.h"
#include "playbackmanager.h"
#include "albumsearchfilter.h"
#include "songfilterproxymodel.h"
#include "albumfilterproxymodel.h"

class SongManager : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(SongFilterProxyModel *songModel READ songModel WRITE setSongModel NOTIFY songModelChanged)
    Q_PROPERTY(AlbumFilterProxyModel *albumSongsModel READ albumSongsModel WRITE setAlbumSongsModel NOTIFY albumSongsModelChanged)
    Q_PROPERTY(AlbumSearchFilter *albumSearchModel READ albumSearchModel WRITE setAlbumSearchModel NOTIFY albumSearchModelChanged)

    Q_PROPERTY(Album currentAlbum READ currentAlbum WRITE setCurrentAlbum NOTIFY currentAlbumChanged)
    //store album info here for now, will change to where each page has its own class
    //which i can access thru view controller, cus i also need to implement go forward and back
    Q_PROPERTY(QString albumName READ albumName WRITE setAlbumName NOTIFY albumNameChanged)
    Q_PROPERTY(QStringList albumArtists READ albumAritsts WRITE setAlbumArtists NOTIFY albumArtistsChanged)
    Q_PROPERTY(QString albumGenre READ albumGenre WRITE setAlbumGenre NOTIFY albumGenreChanged)
    Q_PROPERTY(int albumYear READ albumYear WRITE setAlbumYear NOTIFY albumYearChanged)


public:
    SongManager(PlaybackManager *playbackManager, QObject *parent=nullptr);

    void initPlaylists(PlaylistManager *playlistManager);
    void loadFromSettings();
    void saveToSettings();

    SongFilterProxyModel *songModel() const;
    void setSongModel(SongFilterProxyModel *newSongModel);

    AlbumFilterProxyModel *albumSongsModel() const;
    void setAlbumSongsModel(AlbumFilterProxyModel *newAlbumSongsModel);

    AlbumSearchFilter *albumSearchModel() const;
    void setAlbumSearchModel(AlbumSearchFilter *newAlbumSearchModel);

    Album currentAlbum() const;
    void setCurrentAlbum(const Album &newCurrentAlbum);


    SongListModel *getSongListModel() const;

    AlbumListModel *getAlbumListModel() const;

    QString albumName() const;
    void setAlbumName(const QString &newAlbumName);

    QStringList albumAritsts() const;
    void setAlbumArtists(const QStringList &newAlbumArtists);

    QString albumGenre() const;
    void setAlbumGenre(const QString &newAlbumGenre);

    int albumYear() const;
    void setAlbumYear(int newAlbumYear);

public slots:
    void setAlbum(const Album &album);
signals:
    void songModelChanged();
    void albumSongsModelChanged();
    void albumSearchModelChanged();

    void currentAlbumChanged();


    void albumNameChanged();

    void albumArtistsChanged();

    void albumGenreChanged();

    void albumYearChanged();

private:
    SongListModel *songListModel = nullptr;
    AlbumListModel *albumListModel = nullptr;

    SongFilterProxyModel *m_songModel = nullptr;
    AlbumFilterProxyModel *m_albumSongsModel = nullptr;
    AlbumSearchFilter *m_albumSearchModel = nullptr;
    Album m_currentAlbum;
    QString m_albumName;
    QStringList m_albumArtists;
    QString m_albumGenre;
    int m_albumYear;
};

#endif // SONGMANAGER_H
