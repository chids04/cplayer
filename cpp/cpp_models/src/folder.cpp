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

void Folder::setStored()
{
    storedToFile = true;
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

bool Folder::isStored() const
{
    return storedToFile;
}

QDataStream &operator<<(QDataStream &out, const Folder &folder) {
    out << folder.folderName << folder.folderPath << folder.songCount;
    return out;
}

QDataStream &operator>>(QDataStream &in, Folder &folder) {
    in >> folder.folderName >> folder.folderPath >> folder.songCount;
    return in;
}
