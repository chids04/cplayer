#include "folderview.h"

FolderView::FolderView(QObject *parent)
    : QObject(parent)
{}

FolderView &FolderView::instance()
{
    static FolderView folderView;
    return folderView;
}

void FolderView::startFolderScanningThread(QUrl filePath)
{
    if(!FolderListModel::instance().folderExists(filePath)){
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
    Folder folder(folderName, folderPath, songCount);

    //clearing model since multiple folder support not added yet
    FolderListModel::instance().addFolder(folder);

}

void FolderView::removeFolder(int index, QString folderPath)
{
    FolderListModel::instance().removeFolder(index, folderPath);
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
