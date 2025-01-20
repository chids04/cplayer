#ifndef PLAYLISTIMAGEPROVIDER_H
#define PLAYLISTIMAGEPROVIDER_H

#include <QQuickImageProvider>

class PlaylistImageProvider : public QQuickImageProvider
{
public:
    PlaylistImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    QHash<int, QPixmap> getCovers();
    void addCover(int playlistID, int rotation, const QString &coverPath);
    void loadCovers();
    void saveCovers();
    void removeCover(int playlistID);

private:
    QHash<int, QPixmap> playlistCovers;

};

#endif // PLAYLISTIMAGEPROVIDER_H
