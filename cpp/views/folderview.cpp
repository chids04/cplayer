#include "folderview.h"
#include "folderlistmodel.h"
#include "songlistmodel.h"
#include "albumlistmodel.h"
#include "musicscannerthread.h"
#include "songaddthread.h"
#include "settingsmanager.h"

FolderView::FolderView(QObject *parent)
    : QObject(parent)
{
    connect(this, &FolderView::deleteSongs, &SongListModel::instance(), &SongListModel::removeFolderSongs);
    connect(this, &FolderView::deleteAlbums, &AlbumListModel::instance(), &AlbumListModel::deleteAlbums);

    connect(&this->fsWatch, &QFileSystemWatcher::fileChanged, this, &FolderView::onFileChanged);
    connect(&this->fsWatch, &QFileSystemWatcher::directoryChanged, this, &FolderView::onDirectoryChanged);

    SongAdd *songAdd = new SongAdd;
    songAdd->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, songAdd, &QObject::deleteLater);
    connect(songAdd, &SongAdd::songFetched, &SongListModel::instance(), &SongListModel::onSongAdded);
    connect(songAdd, &SongAdd::songFetched, &AlbumListModel::instance(), &AlbumListModel::updateAlbum);
    connect(this, &FolderView::scanFile, songAdd, &SongAdd::onFileRecieved);
    workerThread.start();
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

        isScanning = true;
        musicScannerThread->start();
    }
}

void FolderView::onScanningFinished(QString folderName, QString folderPath, int songCount)
{
    isScanning = false;

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

void FolderView::onFileChanged(const QString &path)
{
    //for now assume that all changes mean just remove from library
    SongListModel::instance().removeSong(path);

    //create error popup that can show system notifs
}

void FolderView::onDirectoryChanged(const QString &path)
{
    //for now, it deletes on ANY modification, will change to allow renames
    //make sure we are not currently scanning for music in the music scanner thread
    //may modify this so that the whole code runs in a diff thread
    qDebug() << "detected changes in dir" << path;

    if(!isScanning){
        qDebug() << "hello";
        QDir directory(path);
        QStringList updatedDir = directory.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);


        QStringList existingFiles = getFilesInFolder(path);
        QStringList newFiles;

        for(const QString &file : updatedDir){
            if(!existingFiles.contains(file)){
                newFiles.append(file);
            }
        }

        if(!newFiles.isEmpty()){
            //start new scanning thread here
            for(int i=0; i<newFiles.size(); ++i){
                QString fullPath = directory.filePath(newFiles[i]);
                //run in seperate thread
                emit scanFile(fullPath);
            }

            addFilesToFolder(path, newFiles);
        }

        for(const QString &file : existingFiles){
            if(!updatedDir.contains(file)){
                qDebug() << "removing song at" << file;
                removeFilesFromFolder(path, file);
                QString fullPath = directory.filePath(file);
                SongListModel::instance().removeSong(fullPath);
            }
        }
    }

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

void FolderView::addToWatcher(const QString &path)
{
    fsWatch.addPath(path);
}

void FolderView::setPath(const QUrl &newPath)
{
    if (m_path == newPath)
        return;
    m_path = newPath;
    emit pathChanged();
}

void FolderView::setFolderDirHash(const QHash<QString, QStringList> &loadedFileFolderHash)
{
    folderDirHash = loadedFileFolderHash;
}

void FolderView::addFilesToFolder(const QString &folderPath, const QStringList &newFiles)
{
    folderDirHash[folderPath] += newFiles;
}

void FolderView::removeFilesFromFolder(const QString &folderPath, const QString &fileName)
{
    if (folderDirHash.contains(folderPath)) {
        QStringList &files = folderDirHash[folderPath];

        if (files.contains(fileName)) {
            files.removeAll(fileName);
        }
    }
}

void FolderView::removeFolderFromMap(const QString &folderPath)
{
    QString path = folderPath;

    qDebug() << folderDirHash;

    if(folderDirHash.contains(path)) {
        qDebug() << "removing" << path;
        folderDirHash.remove(path);
    }

    qDebug() << folderPath;
    qDebug() << folderDirHash;

    SettingsManager::instance().saveFileFolderMap();
}

QStringList FolderView::getFilesInFolder(const QString &folderPath)
{
    return folderDirHash.value(folderPath, QStringList());
}

QHash<QString, QStringList> FolderView::getFolderFileMap()
{
    return folderDirHash;
}
