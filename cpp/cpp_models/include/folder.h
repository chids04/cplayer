#ifndef FOLDER_H
#define FOLDER_H

#include <QString>

class Folder
{

public:
    Folder(QString &folderName, QString &folderPath, int songCount);
    void setFolderName(QString &newFolderName);
    void setFolderPath(QString &newFolderPath);
    void setSongCount(int songCount);

    QString getFolderName() const;
    QString getFolderPath() const;
    int getSongCount() const;

private:
    QString folderName;
    QString folderPath;
    int songCount;
};

#endif // FOLDER_H

