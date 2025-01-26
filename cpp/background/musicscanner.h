#ifndef SONGADDTHREAD_H
#define SONGADDTHREAD_H

#include <QObject>
#include <QFileInfo>


#include "song.h"
#include "coverimgprovider.h"

class MusicScanner : public QObject{

    Q_OBJECT

public:
    MusicScanner(CoverImgProvider *coverImgProvider, QObject *parent=nullptr);

signals:
    void songFetched(Song*);
    void scanningFinished(QString folderName, QString folderPath, int songCount);
    void saveID(int id);

public slots:
    void onFileRecieved(const QString &songPath);
    void onFolderRecieved(const QUrl &folderPath);

private:
    int id;
    CoverImgProvider *coverImgProvider;
};

#endif // SONGADDTHREAD_H
