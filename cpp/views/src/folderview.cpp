#include "folderview.h"

FolderView::FolderView(SongHolder *songHolder, AlbumHolder *albumHolder, CoverArtHolder *coverArtHolder, FolderListModel *folderListModel, QObject *parent)
    : QObject{parent}, songHolder(songHolder), albumHolder(albumHolder), coverArtHolder(coverArtHolder), folderListModel(folderListModel)
{

}

void FolderView::startFolderScanningThread(QUrl filePath)
{
    MusicScannerThread *musicScannerThread = new MusicScannerThread(filePath, songHolder, albumHolder, coverArtHolder, this);
    connect(musicScannerThread, &MusicScannerThread::scanningFinished, this, &FolderView::onScanningFinished);
    connect(musicScannerThread, &MusicScannerThread::finished, musicScannerThread, &QObject::deleteLater);
    musicScannerThread->start();
}

void FolderView::onScanningFinished(QString folderName, QString folderPath, int songCount)
{
    Folder folder(folderName, folderPath, songCount);
    //clearing model since multiple folder support not added yet
    folderListModel->clear();
    folderListModel->addFolder(folder);

    songHolder->populateModel();
    albumHolder->addToModel();

}
