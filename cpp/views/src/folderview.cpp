#include "folderview.h"

FolderView::FolderView(SongListModel *songListModel, AlbumListModel *albumListModel, FolderListModel *folderListModel, CoverArtHolder *coverArtHolder, QObject *parent)
    : QObject(parent), songListModel(songListModel), albumListModel(albumListModel), folderListModel(folderListModel), coverArtHolder(coverArtHolder)
{

}

void FolderView::startFolderScanningThread(QUrl filePath)
{
    MusicScannerThread *musicScannerThread = new MusicScannerThread(filePath, coverArtHolder, this);
    connect(musicScannerThread, &MusicScannerThread::scanningFinished, this, &FolderView::onScanningFinished);
    connect(musicScannerThread, &MusicScannerThread::songFetched, songListModel, &SongListModel::onSongAdded);
    connect(musicScannerThread, &MusicScannerThread::songFetched, albumListModel, &AlbumListModel::updateAlbum);
    connect(musicScannerThread, &MusicScannerThread::finished, musicScannerThread, &QObject::deleteLater);
    musicScannerThread->start();
}

void FolderView::onScanningFinished(QString folderName, QString folderPath, int songCount)
{
    Folder folder(folderName, folderPath, songCount);
    //clearing model since multiple folder support not added yet
    folderListModel->clear();
    folderListModel->addFolder(folder);

    //songHolder->populateModel();
    //albumHolder->addToModel();

}
