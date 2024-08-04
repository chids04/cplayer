#include "mediaimageprovider.h"

MediaImageProvider::MediaImageProvider():
    QQuickImageProvider(QQuickImageProvider::Pixmap) {}

QPixmap MediaImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QString delimiter = "/";
    QString artist;
    QString albumName;

    int index = id.lastIndexOf(delimiter);

    if(index != -1){
        albumName = id.left(index);
        artist = id.right(id.length()-index-delimiter.length());
    }
    else{
        albumName = id.left(index);
        artist = "";
    }

    QPixmap coverArt;
    QByteArray coverArtBytes;
    coverArtBytes = CoverArtHolder::instance().getCover(artist, albumName);
    coverArt.loadFromData(coverArtBytes);
    coverArt = coverArt.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    return coverArt;
}



