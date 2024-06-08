#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QObject>
#include <QUrl>

#include "musicscannerthread.h"

class FolderView : public QObject
{
    Q_OBJECT
public:
    explicit FolderView(SongHolder *songHolder, AlbumHolder *albumHolder, CoverArtHolder *coverArtHolder, QObject *parent = nullptr);

signals:
    void onSongsLoaded();

public slots:
    void startFolderScanningThread(QUrl filePath);
    void onScanningFinished();

private:
    SongHolder *songHolder;
    AlbumHolder *albumHolder;
    CoverArtHolder *coverArtHolder;
};

#endif // FOLDERVIEW_H
