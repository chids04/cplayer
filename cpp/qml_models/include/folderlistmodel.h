#ifndef FOLDERLISTMODEL_H
#define FOLDERLISTMODEL_H

#include <QUrl>
#include <QList>
#include <QString>
#include <QAbstractListModel>

#include "folder.h"

class FolderListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FolderListModel(QObject *parent = nullptr);
    static FolderListModel &instance();

    enum FolderRoles {
        FolderNameRole = Qt::UserRole + 1,
        FolderPathRole,
        FolderSongCountRole
    };

    void addFolder(const Folder &folder);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QList<Folder> getFolders();
    void removeFolder(int index, QString &folderPath);
    bool folderExists(QUrl &folderPath);
    void clear();

private:
    QList<Folder> m_folders;
};

#endif // FOLDERLISTMODEL_H
