#include "folderview.h"
#include "folderlistmodel.h"
#include "songlistmodel.h"
#include "albumlistmodel.h"
#include "musicscannerthread.h"

FolderView::FolderView(QObject *parent)
    : QObject(parent)
{
    connect(this, &FolderView::deleteSongs, &SongListModel::instance(), &SongListModel::removeFolderSongs);
    connect(this, &FolderView::deleteAlbums, &AlbumListModel::instance(), &AlbumListModel::deleteAlbums);
}

FolderView &FolderView::instance()
{
    static FolderView folderView;
    return folderView;
}

void FolderView::startFolderScanningThread(QUrl filePath, bool firstScan)
{
    if(!FolderListModel::instance().folderExists(filePath) || firstScan){
        MusicScannerThread *musicScannerThread = new MusicScannerThread(filePath, this);
        connect(musicScannerThread, &MusicScannerThread::scanningFinished, this, &FolderView::onScanningFinished);
        connect(musicScannerThread, &MusicScannerThread::songFetched, &SongListModel::instance(), &SongListModel::onSongAdded);
        connect(musicScannerThread, &MusicScannerThread::songFetched, &AlbumListModel::instance(), &AlbumListModel::updateAlbum);
        connect(musicScannerThread, &MusicScannerThread::finished, musicScannerThread, &QObject::deleteLater);
        musicScannerThread->start();
    }
}

void FolderView::onScanningFinished(QString folderName, QString folderPath, int songCount)
{
    QUrl folderURL = QUrl::fromLocalFile(folderPath);
    if(FolderListModel::instance().folderExists(folderURL)){
        return;
    }

    Folder folder(folderName, folderPath, songCount);

    FolderListModel::instance().addFolder(folder);

}

void FolderView::removeFolder(int index, QString folderPath)
{
    //check for songs with matching folderPath (substring of filepath)
    //can do this in respective models
    //emit a signal that notifys the other objects of removed songs
    FolderListModel::instance().removeFolder(index, folderPath);
    //need to delete in songlistmodel, playlistsongsmodel
    emit deleteSongs(folderPath);
    emit deleteAlbums();
}


void FolderView::appendToFile(QUrl &folderPath)
{
    QFile file("config/paths.dat");

    if(file.open(QIODevice::Append | QIODevice::Text)){
        QTextStream out(&file);
        out << folderPath.toString() << "\n";
        file.close();
    }

}

QUrl FolderView::path() const
{
    return m_path;
}

void FolderView::setPath(const QUrl &newPath)
{
    if (m_path == newPath)
        return;
    m_path = newPath;
    emit pathChanged();
}
