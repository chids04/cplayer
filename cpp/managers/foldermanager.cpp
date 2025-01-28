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
    // for now assume that all changes mean just remove from library
    songListModel->removeSong(path);

    // create error popup that can show system notifs
}

void FolderManager::onDirectoryChanged(const QString &path) {
    // for now, it deletes on ANY modification, will change to allow renames
    // make sure we are not currently scanning for music in the music scanner
    // thread may modify this so that the whole code runs in a diff thread
    qDebug() << "detected changes in dir" << path;

    if (!workerThread.isRunning()) {
        qDebug() << "hello";
        QDir directory(path);
        QStringList updatedDir = directory.entryList(
            QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);

        QStringList existingFiles = getFilesInFolder(path);
        QStringList newFiles;

        for (const QString &file : updatedDir) {
            if (!existingFiles.contains(file)) {
                newFiles.append(file);
            }
        }

        if (!newFiles.isEmpty()) {
            // start new scanning thread here
            for (int i = 0; i < newFiles.size(); ++i) {
                QString fullPath = directory.filePath(newFiles[i]);
                // run in seperate thread
                emit scanFile(fullPath);
            }

            addFilesToFolder(path, newFiles);
        }

        for (const QString &file : existingFiles) {
            if (!updatedDir.contains(file)) {
                qDebug() << "removing song at" << file;
                removeFilesFromFolder(path, file);
                QString fullPath = directory.filePath(file);
                songListModel->removeSong(fullPath);
            }
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

    qDebug() << folderDirHash;

    if (folderDirHash.contains(path)) {
        qDebug() << "removing" << path;
        folderDirHash.remove(path);
    }

    qDebug() << folderPath;
    qDebug() << folderDirHash;

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
