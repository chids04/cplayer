#include "folderlistmodel.h"
#include "settingsmanager.h"
#include "foldermanager.h"
#include "songlistmodel.h"

#include "folderlistmodel.h"

#include <QDir>


FolderListModel::FolderListModel(FolderManager *folderManager, QObject *parent) :
    folderManager(folderManager), QAbstractListModel(parent) {}



void FolderListModel::addFolder(const Folder &folder)
{
    folderManager->addToWatcher(folder.getFolderPath());
    QString folderPath = folder.getFolderPath();
    qDebug() << folderPath;

    QDir dir(folderPath);
    QStringList dirList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    folderManager->addFilesToFolder(folderPath, dirList);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_folders << folder;
    endInsertRows();
}
void FolderListModel::removeFolder(int index)
{
    if (index < 0 || index >= m_folders.size()) {
        qWarning() << "removeFolder: invalid index" << index;
        return;
    }

    const Folder &folderToRemove = m_folders[index];
    QString folderPath = folderToRemove.getFolderPath();

    folderManager->removeFolderFromMap(folderPath);

    saveFolders();

    beginRemoveRows(QModelIndex(), index, index);
    m_folders.removeAt(index);
    endRemoveRows();
}

int FolderListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_folders.count();

}

QVariant FolderListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_folders.count()){
        return QVariant();
    }

    const Folder &folder = m_folders[index.row()];

    switch(role) {

        case FolderNameRole:
        return folder.getFolderName();

        case FolderPathRole:
            return folder.getFolderPath();

        case FolderSongCountRole:
            return folder.getSongCount();

        default:
            return QVariant();

    }

}

QHash<int, QByteArray> FolderListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[FolderNameRole] = "folderName";
    roles[FolderPathRole] = "folderPath";
    roles[FolderSongCountRole] = "folderSongCount";

    return roles;
}

QList<Folder> FolderListModel::getFolders()
{
    return m_folders;
}

bool FolderListModel::folderExists(const QUrl &folderPath)
{
    for(const Folder &folder : m_folders) {
        if(folder.getFolderPath() == folderPath.toLocalFile()){
            return true;
        }
    }

    return false;
}


void FolderListModel::scanForChanges(Folder folder)
{
    //on startup, check if songs present on last file save or still present now

    QString folderPath = folder.getFolderPath();
    QString indexFolderPath = folderPath;


    QDir dir(folderPath);
    QStringList dirList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);


    qDebug() << "scanning folder" << folder.getFolderPath() << "for any new songs";
    
    QHash<QString, QStringList> folderFileMap = folderManager->getFolderFileMap();

    QStringList prevDirList = folderFileMap.value(folderPath);
    qDebug() <<  "\nprev dir list" << prevDirList;
    QStringList newFiles;

    for(const QString &file : dirList){
        if(!prevDirList.contains(file)){
            newFiles.append(file);
        }
    }


    if(!newFiles.isEmpty()){
        //start new scanning thread here
        for(int i=0; i<newFiles.size(); ++i){
            QString fullPath = dir.absoluteFilePath(newFiles[i]);
            //run in seperate thread
            emit folderManager->scanFile(fullPath);
        }
        
        folderManager->addFilesToFolder(folderPath, newFiles);
    }


    for(const QString &file : prevDirList){
        if(!dirList.contains(file)){
            folderManager->removeFilesFromFolder(folderPath, file);
            QString fullPath = dir.absoluteFilePath(file);
            folderManager->deleteSongs(fullPath);
        }
    }


    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_folders << folder;
    endInsertRows();
    
    folderManager->addToWatcher(folder.getFolderPath());
}

void FolderListModel::saveFolders()
{
    QSettings settings;

    for(Folder &folder : m_folders){
        folder.setStored();
    }

    settings.setValue("foldersToScan", QVariant::fromValue(m_folders));

    //remove the current info since the saved folders may have been removed in main program
    settings.remove("folderFileMap");
    settings.sync();
    settings.beginGroup("folderFileMap");

    QHash<QString, QStringList> folderFileMap = folderManager->getFolderFileMap();

    for (auto it = folderFileMap.begin(); it != folderFileMap.end(); ++it) {
        QString folderPath = it.key();
        QStringList files = it.value();

        QString fileListString = files.join("%10");
        QString key = QString::number(qHash(folderPath));
        qDebug() << "writing folder" << folderPath << "to file";

        //keys in qsettings cannot contain forward or backslahes so will store hash

        // Join files into a single comma-separated string

        // Save the folder path and corresponding file list
        settings.setValue(key, fileListString);
        settings.setValue(key + "_path", folderPath);
    }

    settings.endGroup();
}


void FolderListModel::readFolders()
{
    QSettings settings;


    settings.beginGroup("folderFileMap");

    QHash<QString, QStringList> folderFileMap;

    // Iterate through all keys (folder paths) in the settings group
    QStringList folderHashes = settings.childKeys();

    qDebug() << "folder file map keys" << folderHashes;

    for (const QString &folderHash : folderHashes) {
        QString folderPath = settings.value(folderHash + "_path").toString();
        QString fileListString = settings.value(folderHash).toString();

        // Split the stored string back into a list of files
        QStringList files = fileListString.split("%10", Qt::SkipEmptyParts);

        // Store in the QHash
        folderFileMap.insert(folderPath, files);
    }


    folderManager->setFolderDirHash(folderFileMap);
    settings.endGroup();

    QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();

    for(const Folder &folder : folders){
        scanForChanges(folder);
    }
}


