#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include <QObject>

#include "albumholder.h"

class AlbumView : public QObject
{
    Q_OBJECT

public:
    explicit AlbumView(QObject *parent = nullptr);

public slots:
    void loadAlbums();

private:
    AlbumHolder *albumHolder;

};

#endif // ALBUMVIEW_H
