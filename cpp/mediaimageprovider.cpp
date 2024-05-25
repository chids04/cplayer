#include "mediaimageprovider.h"

MediaImageProvider::MediaImageProvider(const CoverArtHolder *coverArtHolder):
    QQuickImageProvider(QQuickImageProvider::Pixmap),
    coverArtHolder(coverArtHolder){}

QPixmap MediaImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    //QString localPath = QUrl(id).toLocalFile();
    // QPixmap loadedCover;
    //const char *filePath = QFile::encodeName(id).constData();

    // TagLib::FileRef f = TagLib::FileRef(filePath);

    // TagLib::StringList names = f.complexPropertyKeys();
    // for(const auto &name : names){
    //     const auto& properties = f.complexProperties(name);
    //     for(const auto &property : properties){
    //         for(const auto &[key, value] : property){
    //             if(value.type() == TagLib::Variant::ByteVector){
    //                 loadedCover.loadFromData(QByteArray::fromRawData(value.value<TagLib::ByteVector>().data(),value.value<TagLib::ByteVector>().size()));
    //                 loadedCover = loadedCover.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //             }
    //         }
    //     }
    // }

    //return m_controller->coverArt();
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
    coverArtBytes = coverArtHolder->getCover(artist, albumName);
    coverArt.loadFromData(coverArtBytes);
    coverArt = coverArt.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if(coverArt.isNull()){
        qDebug() << "invalid cover art";
        return QPixmap();
    }

    return coverArt;
}



