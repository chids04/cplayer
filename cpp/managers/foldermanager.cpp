#include "foldermanager.h"
#include "albumlistmodel.h"
#include "folderlistmodel.h"
#include "musicscanner.h"
#include "songlistmodel.h"

FolderManager::FolderManager(SongManager *songManager, CoverImgProvider *coverProvider, QObject *parent)
    : QObject(parent) {
    // add function to load from settings
    setFolderListModel(new FolderListModel(this));
    setSongListModel(songManager->getSongListModel());
    setCoverProvider(coverProvider);

    connect(this, &FolderManager::deleteSongs, songListModel, &SongListModel::removeFolderSongs);
    connect(this, &FolderManager::deleteAlbums, songManager->getAlbumListModel(), &AlbumListModel::deleteAlbums);
    connect(&fsWatch, &QFileSystemWatcher::fileChanged, this, &FolderManager::onFileChanged);
    connect(&fsWatch, &QFileSystemWatcher::directoryChanged, this, &FolderManager::onDirectoryChanged);

    MusicScanner *musicScanner = new MusicScanner(coverProvider);
    musicScanner->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, musicScanner, &QObject::deleteLater);

    connect(this, &FolderManager::scanFile, musicScanner, &MusicScanner::onFileRecieved);
    connect(this, &FolderManager::scanFolder, musicScanner,&MusicScanner::onFolderRecieved);

    connect(this, &FolderManager::songFetched, songListModel, &SongListModel::onSongAdded);
    connect(musicScanner, &MusicScanner::songDataFetched, this, &FolderManager::onSongDataFetched);
    connect(musicScanner, &MusicScanner::scanningFinished, this, &FolderManager::onScanningFinished);
    connect(musicScanner, &MusicScanner::saveID, this, &FolderManager::onSaveID);
    workerThread.start();
}

void FolderManager::startFolderScanningThread(const QUrl &filePath, bool firstScan) {
    if (!m_folderListModel->folderExists(filePath) || firstScan) {
        emit scanFolder(filePath);
    }
}

void FolderManager::onScanningFinished(const QString &folderName, const QString &folderPath, int songCount) {
    QUrl folderURL = QUrl::fromLocalFile(folderPath);

    if (m_folderListModel->folderExists(folderURL)) {
        return;
    }

    Folder folder(folderName, folderPath, songCount);
    m_folderListModel->addFolder(folder);
}

void FolderManager::removeFolder(int index, const QString &folderPath) {
    // check for songs with matching folderPath (substring of filepath)
    // can do this in respective models
    // emit a signal that notifys the other objects of removed songs
    m_folderListModel->removeFolder(index);

    // need to delete in songlistmodel
    emit deleteSongs(folderPath);
    emit deleteAlbums();
}

void FolderManager::onFileChanged(const QString &path) {
    qDebug() << path;
}

void FolderManager::onDirectoryChanged(const QString &path) {
    qDebug() << "Directory changed:" << path;

    QDir directory(path);
    if (!directory.exists()) {
        qWarning() << "Directory does not exist or is not accessible:" << path;
        return;
    }

    QStringList currentFilesInDirList = directory.entryList(
        QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    QSet<QString> currentFilesInDirSet = QSet<QString>(currentFilesInDirList.begin(), currentFilesInDirList.end());

    QStringList existingFilesList = getFilesInFolder(path); 
    qDebug() << existingFilesList;
    QSet<QString> existingFilesSet = QSet<QString>(existingFilesList.begin(), existingFilesList.end());

    QSet<QString> newFilesSet = currentFilesInDirSet;
    newFilesSet.subtract(existingFilesSet);

    if (!newFilesSet.isEmpty()) {
        QStringList newFilesList;
        for(const QString& file : newFilesSet){
            newFilesList.append(file);
        }

        qDebug() << "New files detected in" << path << ":" << newFilesList;
        for (const QString &file : newFilesList) {
            QString fullPath = directory.filePath(file);
            emit scanFile(fullPath);
        }
        addFilesToFolder(path, newFilesList);
    }

    QSet<QString> removedFilesSet = existingFilesSet;
    removedFilesSet.subtract(currentFilesInDirSet);

    if (!removedFilesSet.isEmpty()){
        QStringList removedFilesList;
         for(const QString& file : removedFilesSet){
            removedFilesList.append(file);
        }
        qDebug() << "Removed files detected in" << path << ":" << removedFilesList;
        
        for (const QString &file : removedFilesList) {
            removeFilesFromFolder(path, file); 
            QString fullPath = directory.filePath(file);
            songListModel->removeSong(fullPath);
        }
    }
}

void FolderManager::onSaveID(int id)
{
    QSettings settings;
    settings.setValue("lastSongID", id);
}

void FolderManager::onSongDataFetched(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre, const QStringList &featuringArtists, const QStringList &albumArtists, int year, int length, int trackNum, int id)
{
    Song *song = new Song(filePath, title, artist, album, genre, featuringArtists, albumArtists
                          ,year, length, trackNum, id);

    emit songFetched(song);


}

void FolderManager::appendToFile(QUrl &folderPath) {
    QFile file("config/paths.dat");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << folderPath.toString() << "\n";
        file.close();
    }
}

void FolderManager::setCoverProvider(CoverImgProvider *newCoverProvider)
{
    coverProvider = newCoverProvider;
}

void FolderManager::setSongListModel(SongListModel *newSongListModel)
{
    songListModel = newSongListModel;
}

QUrl FolderManager::path() const { return m_path; }

void FolderManager::addToWatcher(const QString &path) { fsWatch.addPath(path); }

void FolderManager::setPath(const QUrl &newPath) {
    if (m_path == newPath)
        return;
    m_path = newPath;
    emit pathChanged();
}

void FolderManager::setFolderDirHash(
    const QHash<QString, QStringList> &loadedFileFolderHash) {
    folderDirHash = loadedFileFolderHash;
}

void FolderManager::addFilesToFolder(const QString &folderPath,
    const QStringList &newFiles) {
    folderDirHash[folderPath] += newFiles;
}

void FolderManager::removeFilesFromFolder(const QString &folderPath,
    const QString &fileName) {
    if (folderDirHash.contains(folderPath)) {
        QStringList &files = folderDirHash[folderPath];

        if (files.contains(fileName)) {
            files.removeAll(fileName);
        }
    }
}

void FolderManager::removeFolderFromMap(const QString &folderPath) {
    QString path = folderPath;


    if (folderDirHash.contains(path)) {
        folderDirHash.remove(path);
    }


    m_folderListModel->saveFolders();
}

void FolderManager::saveToSettings()
{
    m_folderListModel->saveFolders();
    coverProvider->saveCoverArts();
}

void FolderManager::loadFromSettings()
{
    m_folderListModel->readFolders();
    coverProvider->loadFromSettings();
}

QStringList FolderManager::getFilesInFolder(const QString &folderPath) {
    return folderDirHash.value(folderPath, QStringList());
}

QHash<QString, QStringList> FolderManager::getFolderFileMap() {
    return folderDirHash;
}

FolderListModel *FolderManager::folderListModel() const {
    return m_folderListModel;
}

void FolderManager::setFolderListModel(FolderListModel *newFolderListModel) {
    if (m_folderListModel == newFolderListModel)
        return;
    m_folderListModel = newFolderListModel;
    emit folderListModelChanged();
}
