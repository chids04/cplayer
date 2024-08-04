#ifndef MUSICSCANNERTHREAD_H
#define MUSICSCANNERTHREAD_H

#include <QUrl>
#include <QtQml>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QPixmap>
#include <QFileInfo>
#include <QStringList>
#include <QDirIterator>
#include <QQmlListProperty>

#include <vector>
#include <memory>

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

#include "song.h"
#include "coverartholder.h"

//this class needs to get
//list of albums
//list of songs

class MusicScannerThread : public QThread
{
    Q_OBJECT
    void run() override;

public:
    explicit MusicScannerThread(QUrl musicPath, QObject *parent = nullptr);

signals:
    void songFetched(std::shared_ptr<Song>);
    void scanningFinished(QString folderName, QString folderPath, int songCount);

private:
    QUrl musicPath;

};

#endif // MUSICSCANNERTHREAD_H
