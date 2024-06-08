#ifndef MEDIAIMAGEPROVIDER_H
#define MEDIAIMAGEPROVIDER_H

#include <QUrl>
#include <QFile>
#include <QString>
#include <QQuickImageProvider>
#include <QStringList>
#include <QByteArray>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>

#include "coverartholder.h"

class MediaImageProvider : public QQuickImageProvider
{
public:
    MediaImageProvider(const CoverArtHolder *coverArtHolder);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    const CoverArtHolder *coverArtHolder;
};

#endif // MEDIAIMAGEPROVIDER_H
