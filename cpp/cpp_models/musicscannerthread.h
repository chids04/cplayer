#ifndef MUSICSCANNERTHREAD_H
#define MUSICSCANNERTHREAD_H

#include <QUrl>
#include <QObject>
#include <QThread>
#include <memory>

#include "song.h"

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
    int id;

};

#endif // MUSICSCANNERTHREAD_H
