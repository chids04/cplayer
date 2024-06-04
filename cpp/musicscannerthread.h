#ifndef MUSICSCANNERTHREAD_H
#define MUSICSCANNERTHREAD_H

#include <QUrl>
#include <QtQml>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QPixmap>
#include <QStringList>
#include <QDirIterator>
#include <QQmlListProperty>

#include <vector>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

#include "songlistmodel.h"
#include "coverartholder.h"
#include "albumholder.h"
#include "songholder.h"

//this class needs to get
//list of albums
//list of songs

class MusicScannerThread : public QThread
{
    Q_OBJECT
    void run() override;

public:
    explicit MusicScannerThread(QUrl musicPath, SongHolder *songHolder, AlbumHolder *albumHolder, CoverArtHolder *coverArtHolder, QObject *parent = nullptr);

signals:
    void songFetched(Song song);
    void scanningFinished();

private:
    QUrl musicPath;
    AlbumHolder *albumHolder;
    CoverArtHolder *coverArtHolder;
    SongHolder *songHolder;

};

#endif // MUSICSCANNERTHREAD_H
