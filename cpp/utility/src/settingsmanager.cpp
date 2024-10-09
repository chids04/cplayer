#include "settingsmanager.h"

#include <QSettings>
#include "folderlistmodel.h"
#include "folderview.h"
#include "nowplaying.h"
#include "songlistmodel.h"
#include "coverartholder.h"
#include "albumlistmodel.h"
#include "mediaplayercontroller.h"

#include <QDebug>

SettingsManager::SettingsManager(QObject *parent)
{
    connect(this ,&SettingsManager::songLoaded, &SongListModel::instance(), &SongListModel::onSongAdded);
    connect(this, &SettingsManager::songLoaded, &AlbumListModel::instance(), &AlbumListModel::updateAlbum);
}

SettingsManager &SettingsManager::instance()
{
    static SettingsManager settingsManager;
    return settingsManager;
}

void SettingsManager::setup()
{
    readFolders();
    readSongs();
    CoverArtHolder::instance().loadFromSettings();
    NowPlaying::instance().loadFromSettings();
}

bool SettingsManager::hasFolder()
{
    QSettings settings;

    if(settings.contains("foldersToScan")){
        return true;
    }
    else{
        return false;
    }
}

void SettingsManager::writeFolder(const Folder &folder)
{
    QSettings settings;

    if(hasFolder()){
        QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();

        for(const Folder &storedFolder : folders){
            if(storedFolder.getFolderPath() == folder.getFolderPath()){
                return;
            }
        }

        folders.append(folder);
        settings.setValue("foldersToScan", QVariant::fromValue(folders));
    }
    else{
        QList<Folder> folders;
        folders.append(folder);
        settings.setValue("foldersToScan", QVariant::fromValue(folders));
    }
}

void SettingsManager::readFolders()
{
    QSettings settings;
    QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();

    for(const Folder &folder : folders){
        FolderListModel::instance().addFolder(folder);
        //FolderView::instance().startFolderScanningThread(QUrl::fromLocalFile(folder.getFolderPath()), true);
    }


}

void SettingsManager::readSongs()
{
    QSettings settings;
    QList<Song> songs = settings.value("songs").value<QList<Song>>();

    for(const Song &song : songs){
        std::shared_ptr<Song> songPtr = std::make_shared<Song>(song);

        emit songLoaded(songPtr);
    }
}

void SettingsManager::removeFolder(QString &folderPath)
{
    QSettings settings;
    settings.sync(); //committing all changes

    QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();

    for(int i=0; i<folders.count();i++){
        if(folders[i].getFolderPath() == folderPath){
            folders.removeAt(i);
        }
    }

    settings.setValue("foldersToScan", QVariant::fromValue(folders));

}

void SettingsManager::saveNowPlaying()
{
    //only need to store song id
    QList<std::shared_ptr<Song>> nowPlaying = NowPlaying::instance().getNowPlaying();
    int currentIndex = NowPlaying::instance().getCurrentIndex();
    qint64 position = MediaPlayerController::instance().position();

    QList<int> idList;

    for(const auto &song : nowPlaying){
        idList << song->id;
    }

    QSettings settings;
    settings.setValue("nowPlayingList", QVariant::fromValue(idList));
    settings.setValue("nowPlayingCurrentIndex", currentIndex);
    settings.setValue("nowPlayingSongPosition", QVariant::fromValue(position));
}

void SettingsManager::saveFolders()
{
    QSettings settings;

    QList<Folder> folders = FolderListModel::instance().getFolders();
    for(Folder &folder : folders){
        folder.setStored();
    }

    settings.setValue("foldersToScan", QVariant::fromValue(folders));
}

void SettingsManager::saveSongs()
{
    QSettings settings;
    QList<std::shared_ptr<Song>> songs = SongListModel::instance().getSongs();
    QList<Song> songObj;

    for(const auto &song: songs){
        songObj.append(*song);
    }

    settings.setValue("songs", QVariant::fromValue(songObj));
}

void SettingsManager::saveCoverArts()
{
    QSettings settings;

    QHash<CoverArtKey, QByteArray> covers = CoverArtHolder::instance().getAllCovers();
    settings.beginGroup("CoverArts");

    for (auto it = covers.begin(); it != covers.end(); ++it) {
        QString key = it.key().toString();  // Convert CoverArtKey to QString
        QByteArray coverArt = it.value();
        settings.setValue(key, coverArt);  // Store the cover art
    }

    settings.endGroup();
}

void SettingsManager::shutDown()
{
    saveNowPlaying();
    saveSongs();
    saveCoverArts();
    saveFolders();
}















