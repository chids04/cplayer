#include "folderview.h"

FolderView::FolderView(SongHolder *songHolder, AlbumHolder *albumHolder, CoverArtHolder *coverArtHolder, QObject *parent)
    : QObject{parent}, songHolder(songHolder), albumHolder(albumHolder), coverArtHolder(coverArtHolder)
{

}

void FolderView::startFolderScanningThread(QUrl filePath)
{
    MusicScannerThread *musicScannerThread = new MusicScannerThread(filePath, songHolder, albumHolder, coverArtHolder, this);
    connect(musicScannerThread, &MusicScannerThread::scanningFinished, this, &FolderView::onScanningFinished);
    connect(musicScannerThread, &MusicScannerThread::finished, musicScannerThread, &QObject::deleteLater);
    musicScannerThread->start();
}

void FolderView::onScanningFinished()
{
    songHolder->populateModel();

}
