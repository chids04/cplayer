#ifndef PLAYLISTSONGSMANAGER_H
#define PLAYLISTSONGSMANAGER_H

#include <QObject>

class PlaylistSongsManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString playlistName READ playlistName WRITE setPlaylistName NOTIFY playlistNameChanged)
    Q_PROPERTY(bool hasCover READ hasCover WRITE setHasCover NOTIFY hasCoverChanged)
    Q_PROPERTY(int playlistID READ playlistID WRITE setPlaylistID NOTIFY playlistIDChanged)

public:
    static PlaylistSongsManager &instance();

    int playlistID() const;
    void setPlaylistID(int newPlaylistID);

    bool hasCover() const;
    void setHasCover(bool newHasCover);

    QString playlistName() const;
    void setPlaylistName(const QString &newPlaylistName);

signals:
    void playlistIDChanged();

    void hasCoverChanged();

    void playlistNameChanged();

private:
    int m_playlistID;
    bool m_hasCover;
    QString m_playlistName;
};

#endif // PLAYLISTSONGSMANAGER_H
