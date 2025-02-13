#include "coverimgprovider.h"

#include <QFile>
#include <QByteArray>
#include <QStringList>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>


CoverImgProvider::CoverImgProvider() :
    QQuickImageProvider(QQuickImageProvider::Pixmap) {}


QPixmap CoverImgProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QString delimiter = "++?";
    QStringList artists;
    QString albumName;

    int index = id.lastIndexOf("/");

    if(index != -1){
        albumName = id.left(index);
        QString artistStr = id.mid(index+1);

        artists = artistStr.split("++?");


        QPixmap coverArt;

        QByteArray coverArtBytes;
        coverArtBytes = getCover(artists, albumName);
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

void CoverImgProvider::addCover(const QStringList &artists, const QString &albumName, QByteArray &coverArt)
{
    if(coverArt.isEmpty()){
        return;
    }

    CoverArtKey key = {artists, albumName};

    coverArts.insert(key, coverArt);
}

QByteArray CoverImgProvider::getCover(const QStringList &artists, const QString &albumName) const
{
    CoverArtKey key = {artists, albumName};

    if(coverArts.contains(key)){
        return coverArts.value(key);
    }
    return QByteArray();
}

bool CoverImgProvider::hasCover(const QStringList &artists, const QString &albumName) const
{
    CoverArtKey key = {artists, albumName};
    return coverArts.contains(key);
}

void CoverImgProvider::loadFromSettings()
{
    QSettings settings;
    settings.beginGroup("CoverArts");

    QStringList keys = settings.childKeys();
    for (const QString &key : keys) {
        CoverArtKey coverKey = CoverArtKey::fromString(key);  // Convert string back to CoverArtKey
        QByteArray coverArt = settings.value(key).toByteArray();
        coverArts.insert(coverKey, coverArt);  // Insert into the QHash
    }

    settings.endGroup();
}


void CoverImgProvider::saveCoverArts()
{
    QSettings settings;

    settings.beginGroup("CoverArts");

    for (auto it = coverArts.begin(); it != coverArts.end(); ++it) {
        QString key = it.key().toString();  // Convert CoverArtKey to QString
        QByteArray coverArt = it.value();
        settings.setValue(key, coverArt);  // Store the cover art
    }

    settings.endGroup();
}



