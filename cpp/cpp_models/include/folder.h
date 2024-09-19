#ifndef FOLDER_H
#define FOLDER_H

#include <QString>
#include <QMetaType>
#include <QDataStream>

class Folder
{

public:
    Folder() = default;

    Folder(QString &folderName, QString &folderPath, int songCount);

    void setFolderName(QString &newFolderName);
    void setFolderPath(QString &newFolderPath);
    void setSongCount(int songCount);

    QString getFolderName() const;
    QString getFolderPath() const;
    int getSongCount() const;

    friend QDataStream &operator<<(QDataStream &out, const Folder &folder);

    friend QDataStream &operator>>(QDataStream &in, Folder &folder);

private:
    QString folderName;
    QString folderPath;
    int songCount;
};

Q_DECLARE_METATYPE(Folder)
#endif // FOLDER_H

