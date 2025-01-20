#include "playlistimageprovider.h"

#include <QSettings>
#include <QPixmap>
#include <QString>
#include <QGlobalStatic>

PlaylistImageProvider::PlaylistImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{}

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

void PlaylistImageProvider::addCover(int playlistID, int rotation, const QString &coverPath)
{
    QPixmap cover(coverPath);

    if(!cover.isNull()){


        if(rotation > 0){
            cover = cover.transformed(QTransform().rotate(rotation));
        }

        cover = cover.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        playlistCovers.insert(playlistID, cover);
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

void PlaylistImageProvider::saveCovers()
{
    QSettings settings;
    settings.remove("playlistCovers");
    settings.sync();
    settings.beginGroup("playlistCovers");

    for(auto it = playlistCovers.begin(); it != playlistCovers.end(); ++it){
        int coverKey = it.key();
        QPixmap coverArt = it.value();

        settings.setValue(QString::number(coverKey), coverArt);
    }

    settings.endGroup();
}

void PlaylistImageProvider::removeCover(int playlistID)
{
    playlistCovers.remove(playlistID);
}

