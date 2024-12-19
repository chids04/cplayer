#ifndef SONGADDTHREAD_H
#define SONGADDTHREAD_H

#include <QObject>
#include <QFileInfo>
#include <QDirIterator>

#include "song.h"

class SongAdd : public QObject{

    Q_OBJECT

public:
    SongAdd(QObject *parent=nullptr);

signals:
    void songFetched(std::shared_ptr<Song>);

public slots:
    void onFileRecieved(const QString &songPath);

private:
    int id;
};

#endif // SONGADDTHREAD_H
