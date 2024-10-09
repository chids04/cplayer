#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <memory>

#include <QObject>

#include "folder.h"
#include "song.h"

class SettingsManager : public QObject{

    Q_OBJECT

public:
    SettingsManager(QObject *parent=nullptr);
    static SettingsManager &instance();

    void setup();
    bool hasFolder();
    void writeFolder(const Folder &folder);
    void readFolders();
    void readSongs();
    void removeFolder(QString &folderPath);

    void saveNowPlaying();
    void saveFolders();
    void saveSongs();
    void saveCoverArts();
    void saveAlbums();

public slots:
    void shutDown();

signals:
    void songLoaded(std::shared_ptr<Song>);


};

#endif // SETTINGSMANAGER_H

