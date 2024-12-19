#include "mediaimageprovider.h"

#include <QFile>
#include <QByteArray>
#include <QStringList>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>

#include "coverartholder.h"

MediaImageProvider::MediaImageProvider():
    QQuickImageProvider(QQuickImageProvider::Pixmap) {}

QPixmap MediaImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QString delimiter = "/";
    QStringList artists;
    QString albumName;

    int index = id.lastIndexOf(delimiter);

    if(index != -1){
        albumName = id.left(index);
        artists = id.right(id.length()-index-delimiter.length()).split('%');

        QPixmap coverArt;

        QByteArray coverArtBytes;
        coverArtBytes = CoverArtHolder::instance().getCover(artists, albumName);
        coverArt.loadFromData(coverArtBytes);

        if(coverArt.isNull()){
            QPixmap defaultCover(":/resource/ui/assets/unknownCover.png");
            defaultCover = defaultCover.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

            return defaultCover;
        }

        coverArt = coverArt.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        return coverArt;

    }
    else{

        QPixmap defaultCover(":/resource/ui/assets/unknownCover.png");
        defaultCover = defaultCover.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        return defaultCover;
    }

}



