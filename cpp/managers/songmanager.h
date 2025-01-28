#ifndef SONGMANAGER_H
#define SONGMANAGER_H

#include <QObject>
#include <QStringListModel>
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

    //stringlistmodels for song editing
    Q_PROPERTY(QStringListModel *featuresList READ featuresList WRITE setFeaturesList NOTIFY featuresListChanged)
    Q_PROPERTY(QStringListModel *albumArtistsList READ albumArtistsList WRITE setAlbumArtistsList NOTIFY albumAritstsListChanged)



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

    QStringListModel *featuresList() const;
    void setFeaturesList(QStringListModel *newFeaturesList);

    QStringListModel *albumArtistsList() const;
    void setAlbumArtistsList(QStringListModel *newAlbumArtistsList);

public slots:
    void setAlbum(const Album &album);

    //song editing functions
    void insertFeature(const QString &feature);
    void setFeaturesToEdit(const QStringList &features);
    void moveFeature(int src, int dst);
    void removeFeature(int index);

    void insertArtist(const QString &artist);
    void setAlbumArtistsToEdit(const QStringList &albumArtists);
    void moveArtist(int src, int dst);
    void removeArtist(int index);
    void saveChanges(Song *song, const QString &title, const QString &leadingArtist, const QString &album,
                     const QString &genre, int year, int trackNum, bool hasCover, const QUrl &coverPath = QUrl());

signals:
    void songModelChanged();
    void albumSongsModelChanged();
    void albumSearchModelChanged();

    void currentAlbumChanged();


    void albumNameChanged();

    void albumArtistsChanged();

    void albumGenreChanged();

    void albumYearChanged();

    void featuresListChanged();

    void albumAritstsListChanged();

private:
    SongListModel *songListModel = nullptr;
    AlbumListModel *albumListModel = nullptr;
    MediaPlayerController *mediaPlayer = nullptr;

    SongFilterProxyModel *m_songModel = nullptr;
    AlbumFilterProxyModel *m_albumSongsModel = nullptr;
    AlbumSearchFilter *m_albumSearchModel = nullptr;
    Album m_currentAlbum;
    QString m_albumName;
    QStringList m_albumArtists;
    QString m_albumGenre;
    int m_albumYear;
    QStringListModel *m_featuresList = nullptr;
    QStringListModel *m_albumArtistsList = nullptr;
};

#endif // SONGMANAGER_H
