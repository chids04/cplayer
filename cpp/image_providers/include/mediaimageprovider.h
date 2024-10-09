#ifndef MEDIAIMAGEPROVIDER_H
#define MEDIAIMAGEPROVIDER_H

#include <QUrl>
#include <QString>
#include <QQuickImageProvider>



class MediaImageProvider : public QQuickImageProvider
{

public:
    MediaImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

};

#endif // MEDIAIMAGEPROVIDER_H
