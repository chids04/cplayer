#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QObject>
#include <QUrl>

#include "folderlistmodel.h"
#include "musicscannerthread.h"

class FolderView : public QObject
{
    Q_OBJECT
public:
    explicit FolderView(SongHolder *songHolder, AlbumHolder *albumHolder, CoverArtHolder *coverArtHolder, FolderListModel *folderListModel,
                        QObject *parent = nullptr);

signals:
    void onSongsLoaded();

public slots:
    void startFolderScanningThread(QUrl filePath);
    void onScanningFinished(QString folderName, QString folderPath, int songCount);

private:
    SongHolder *songHolder;
    AlbumHolder *albumHolder;
    CoverArtHolder *coverArtHolder;
    FolderListModel *folderListModel;
};

#endif // FOLDERVIEW_H
