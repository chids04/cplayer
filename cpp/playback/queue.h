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
    Queue(QString name, QList<std::shared_ptr<Song>> songs, QObject *parent = nullptr);
    QList<std::shared_ptr<Song>> getSongs();
    void shuffleSongs();
    std::shared_ptr<Song> popSong();
    QString queueName() const;
    void queueName(const QString &newQueueName);

signals:
    void queueNameChanged();

private:
    QString m_queueName;
    bool shuffle = false;
    QList<std::shared_ptr<Song>> originalSongs;
    QList<std::shared_ptr<Song>> shuffledSongs;
};

#endif // QUEUE_H
