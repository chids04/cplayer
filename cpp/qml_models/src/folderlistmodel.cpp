#include "folderlistmodel.h"
#include "settingsmanager.h"


FolderListModel::FolderListModel(QObject *parent) : QAbstractListModel(parent) {}

FolderListModel &FolderListModel::instance()
{
    static FolderListModel folderListModel;
    return folderListModel;
}

void FolderListModel::addFolder(const Folder &folder)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_folders << folder;
    endInsertRows();
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

void FolderListModel::removeFolder(int index, QString &folderPath)
{
    if(index < 0 || index >=m_folders.count()){
        return;
    }

    //if folder written to file then it needs to be deleted from there too
    if(m_folders[index].isStored()){
        SettingsManager::instance().removeFolder(folderPath);
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_folders.removeAt(index);
    endRemoveRows();



}

bool FolderListModel::folderExists(QUrl &folderPath)
{
    for(const Folder &folder : m_folders) {
        if(folder.getFolderPath() == folderPath.toLocalFile()){
            return true;
        }
    }

    return false;
}

void FolderListModel::clear()
{
    if(!m_folders.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_folders.count() - 1);
        m_folders.clear();
        endRemoveRows();
    }
}


