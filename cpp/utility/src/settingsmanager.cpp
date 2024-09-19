#include "settingsmanager.h"
#include "folderlistmodel.h"

SettingsManager::SettingsManager(QObject *parent)
{
}

SettingsManager &SettingsManager::instance()
{
    static SettingsManager settingsManager;
    return settingsManager;
}

bool SettingsManager::hasFolder()
{
    QSettings settings;

    if(settings.contains("foldersToScan")){
        return true;
    }
    else{
        return false;
    }
}

void SettingsManager::writeFolder(const Folder &folder)
{
    QSettings settings;

    if(hasFolder()){
        QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();

        for(const Folder &storedFolder : folders){
            if(storedFolder.getFolderPath() == folder.getFolderPath()){
                return;
            }
        }

        folders.append(folder);
        settings.setValue("foldersToScan", QVariant::fromValue(folders));
        qDebug() << "wrote folder to file";
    }
    else{
        QList<Folder> folders;
        folders.append(folder);
        settings.setValue("foldersToScan", QVariant::fromValue(folders));
    }
}

void SettingsManager::readFolders()
{
    QSettings settings;
    QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();

    for(const Folder &folder : folders){
        FolderListModel::instance().addFolder(folder);
    }
}

void SettingsManager::removeFolder(QString &folderPath)
{
    QSettings settings;
    settings.sync(); //committing all changes

    QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();
    for(int i=0; i<folders.count();i++){
        if(folders[i].getFolderPath() == folderPath){
            folders.removeAt(i);
        }
    }
    settings.setValue("foldersToScan", QVariant::fromValue(folders));
    qDebug() << "deleted from settings";

}








