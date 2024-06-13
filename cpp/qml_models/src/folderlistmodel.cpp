#include "folderlistmodel.h"

FolderListModel::FolderListModel(QObject *parent) : QAbstractListModel(parent) {}

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

void FolderListModel::clear()
{
    if(!m_folders.isEmpty()){
        beginRemoveRows(QModelIndex(), 0, m_folders.count() - 1);
        m_folders.clear();
        endRemoveRows();
    }
}


