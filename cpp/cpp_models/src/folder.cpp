#include "folder.h"

Folder::Folder(QString &folderName, QString &folderPath, int songCount) : folderName(folderName), folderPath(folderPath), songCount(songCount)
{}

void Folder::setFolderName(QString &newFolderName)
{
    folderName = newFolderName;
}

void Folder::setFolderPath(QString &newFolderPath)
{
    folderPath = newFolderPath;
}

void Folder::setSongCount(int newSongCount)
{
    songCount = newSongCount;
}

QString Folder::getFolderName() const
{
    return folderName;
}

QString Folder::getFolderPath() const
{
    return folderPath;
}

int Folder::getSongCount() const
{
    return songCount;
}
