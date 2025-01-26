#ifndef QUEUE_H
#define QUEUE_H

#include <QObject>
#include <QList>
#include <random>

#include "song.h"

//will replace the QList with a QAbstractItemModel to allow reordering the queue from the GUI
class Queue : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString queueName READ queueName WRITE queueName NOTIFY queueNameChanged);

public:
    Queue(QString name, QList<Song*> songs, QObject *parent = nullptr);
    QList<Song*> getSongs();
    void shuffleSongs();
    Song* popSong();
    QString queueName() const;
    void queueName(const QString &newQueueName);

signals:
    void queueNameChanged();

private:
    QString m_queueName;
    bool shuffle = false;
    QList<Song*> originalSongs;
    QList<Song*> shuffledSongs;
};

#endif // QUEUE_H
