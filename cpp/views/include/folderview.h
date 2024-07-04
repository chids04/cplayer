#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QObject>
#include <QUrl>

#include "folderlistmodel.h"
#include "songlistmodel.h"
#include "albumlistmodel.h"
#include "musicscannerthread.h"
#include "coverartholder.h"

class FolderView : public QObject
{
    Q_OBJECT
public:
    explicit FolderView(SongListModel *songlistModel, AlbumListModel *albumListModel, FolderListModel *folderListModel, CoverArtHolder *coverArtHolder, QObject *parent = nullptr);

signals:
    void onSongsLoaded();

public slots:
    void startFolderScanningThread(QUrl filePath);
    void onScanningFinished(QString folderName, QString folderPath, int songCount);

private:
    SongListModel *songListModel;
    AlbumListModel *albumListModel;
    FolderListModel *folderListModel;
    CoverArtHolder *coverArtHolder;
};

#endif // FOLDERVIEW_H
