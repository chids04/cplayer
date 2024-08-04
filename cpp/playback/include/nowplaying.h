#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include <QObject>

#include "song.h"
#include "albumlistmodel.h"

class NowPlaying : public QObject
{
    Q_OBJECT

public:
    explicit NowPlaying(QObject *parent = nullptr);
    static NowPlaying &instance();
    static NowPlaying *create(QQmlEngine *engine, QJSEngine *);

signals:
    void playSong(std::shared_ptr<Song> song);
    void jumpToEnd();

public slots:
    void playAlbum(const QString &albumName, const QStringList &albumArtists, bool queue=false);
    void onPreviousClicked(int duration);
    void onNextClicked();
    void queueNext(std::shared_ptr<Song> song);
    void addToQueue(std::shared_ptr<Song> song);
    void playNow(std::shared_ptr<Song> song);

private:
    QList<std::shared_ptr<Song>> songQueue;
    int currentIndex = 0;

};

#endif // NOWPLAYING_H
