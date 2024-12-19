#include "playlistimageprovider.h"

#include <QSettings>
#include <QPixmap>
#include <QString>
#include <QGlobalStatic>

PlaylistImageProvider::PlaylistImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{}

PlaylistImageProvider &PlaylistImageProvider::instance()
{
    static PlaylistImageProvider playlistImageProvider;
    return playlistImageProvider;

}

QPixmap PlaylistImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap loadedCover;

    if(playlistCovers.contains(id.toInt())){
        loadedCover = playlistCovers.value(id.toInt());

        if(loadedCover.isNull()){
            QPixmap defaultCover(":/resource/ui/assets/unknownCover.png");
            defaultCover = defaultCover.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            return defaultCover;
        }

        loadedCover = loadedCover.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return loadedCover;
    }

    else{
        QPixmap defaultCover(":/resource/ui/assets/unknownCover.png");
        defaultCover = defaultCover.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        return defaultCover;
    }
}

QHash<int, QPixmap> PlaylistImageProvider::getCovers()
{
    return playlistCovers;
}

void PlaylistImageProvider::addCover(int playlistID, QString coverPath)
{
    QPixmap cover(coverPath);

    if(!cover.isNull()){
        playlistCovers.insert(playlistID, coverPath);
    }
}

void PlaylistImageProvider::loadCovers()
{
    QSettings settings;
    settings.beginGroup("playlistCovers");

    QStringList keys = settings.childKeys();

    for(const QString &key : keys){
        int playlistID = key.toInt();
        QPixmap coverArt = settings.value(key).value<QPixmap>();

        playlistCovers.insert(playlistID, coverArt);
    }

    settings.endGroup();
}

void PlaylistImageProvider::removeCover(int playlistID)
{
    playlistCovers.remove(playlistID);
}

