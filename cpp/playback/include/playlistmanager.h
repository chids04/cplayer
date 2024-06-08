#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QObject>

#include "playlist.h"
#include "albumholder.h"

class PlaylistManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nextFilePath READ setNextFilePath WRITE nextFilePath NOTIFY onNextFilePathChanged)
    Q_PROPERTY(QString nextTrackTitle READ nextTrackTitle NOTIFY onNextTrackTitleChanged)
    Q_PROPERTY(QString nextLeadingArtist READ nextLeadingArtist NOTIFY nextLeadingArtistChanged)
    Q_PROPERTY(QStringList features READ features WRITE setFeatures NOTIFY featuresChanged)

public:
    explicit PlaylistManager(AlbumHolder *albumHolder, QObject *parent = nullptr);

    QString setNextFilePath() const;
    void nextFilePath(const QString &newNextFilePath);
    QString nextTrackTitle() const;

    QString nextLeadingArtist() const;

    QStringList features() const;
    void setFeatures(const QStringList &newFeatures);

    QString getNextSong();
    QString getPreviousSong();




public slots:
    void playAlbum(const QString &albumName, const QStringList &albumArtists);

signals:
    void onNextFilePathChanged();
    void onNextTrackTitleChanged();
    void playlistQueued();
    void nextLeadingArtistChanged();

    void featuresChanged();

private:
    QString m_nextFilePath;
    QString m_nextTrackTitle;
    QString m_nextLeadingArtist;
    QStringList m_features;
    AlbumHolder *albumHolder;
    QList<Playlist> playlists;

    int currentPlaylistID;
};

#endif // PLAYLISTMANAGER_H
