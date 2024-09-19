#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>

#include "folder.h"

class SettingsManager : public QObject{

    Q_OBJECT

public:
    SettingsManager(QObject *parent=nullptr);
    static SettingsManager &instance();

    bool hasFolder();
    void writeFolder(const Folder &folder);
    void readFolders();
    void removeFolder(QString &folderPath);

};

#endif // SETTINGSMANAGER_H

