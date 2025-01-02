#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <memory>

#include <QObject>
#include <QHash>

#include "folder.h"
#include "song.h"
#include "playlistimageprovider.h"

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
    void readPlaylists();
    void readFileFolderMap();
    void readPlaylistCovers();
    void removeFolder(QString &folderPath);
    QHash<QString,QStringList> getFolderFileMap();

    void saveNowPlaying();
    void saveFolders();
    void saveSongs();
    void saveCoverArts();
    void saveAlbums();
    void savePlaylists();
    void saveFileFolderMap();
    void savePlaylistCovers();

    void setPlaylistImageProvider(PlaylistImageProvider *img_provider);

public slots:
    void shutDown();

signals:
    void songLoaded(std::shared_ptr<Song>);
    void folderLoaded(Folder folder);

private:
    QHash<QString, QStringList> loadedFileFolderMap;
    PlaylistImageProvider *playlistImageProvider;

};

#endif // SETTINGSMANAGER_H

