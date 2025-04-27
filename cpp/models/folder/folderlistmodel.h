#ifndef FOLDERLISTMODEL_H
#define FOLDERLISTMODEL_H

#include <QUrl>

#include <QList>
#include <QString>
#include <QAbstractListModel>
#include <qqmlintegration.h>

#include "folder.h"

class FolderManager;

class FolderListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ANONYMOUS

public:
    explicit FolderListModel(FolderManager *folderManager, QObject *parent = nullptr);

    enum FolderRoles {
        FolderNameRole = Qt::UserRole + 1,
        FolderPathRole,
        FolderSongCountRole
    };

    void addFolder(const Folder &folder);
    void removeFolder(int index);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QList<Folder> getFolders();

    bool folderExists(const QUrl &folderPath);
    void saveFolders();
    void readFolders();
    bool scanForChanges(const Folder &folder);

public slots:

private:
    QList<Folder> m_folders;
    FolderManager *folderManager;

};

#endif // FOLDERLISTMODEL_H
