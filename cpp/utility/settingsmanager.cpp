#include "settingsmanager.h"

#include <QSettings>
#include "folderlistmodel.h"
#include "folderview.h"
#include "nowplaying.h"
#include "songlistmodel.h"
#include "coverartholder.h"
#include "albumlistmodel.h"
#include "mediaplayercontroller.h"
#include "playlistmodel.h"
#include "playlistmanager.h"
#include "playlistimageprovider.h"

#include <QDebug>

SettingsManager::SettingsManager(QObject *parent)
{
    connect(this ,&SettingsManager::songLoaded, &SongListModel::instance(), &SongListModel::onSongAdded);
    connect(this, &SettingsManager::songLoaded, &AlbumListModel::instance(), &AlbumListModel::updateAlbum);
    connect(this, &SettingsManager::folderLoaded, &FolderListModel::instance(), &FolderListModel::onFolderLoaded);
}

SettingsManager &SettingsManager::instance()
{
    static SettingsManager settingsManager;
    return settingsManager;
}

void SettingsManager::setup()
{
    readSongs();
    readFileFolderMap();
    readFolders();
    readPlaylists();
    CoverArtHolder::instance().loadFromSettings();
    PlaylistImageProvider::instance().loadCovers();
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
        //change herex
        emit folderLoaded(folder);

        //add logic to recheck folders on login to make sure files still there
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

void SettingsManager::readPlaylists()
{
    QSettings settings;
    QList<Playlist> loadedPlaylists = settings.value("playlists").value<QList<Playlist>>();
    int playlistNum = settings.value("playlistNum", 0).toInt();

    QList<std::shared_ptr<Playlist>> playlistPtrs;

    for(const Playlist &playlist : loadedPlaylists){
        std::shared_ptr<Playlist> playlistPtr = std::make_shared<Playlist>(playlist);
        playlistPtrs.append(playlistPtr);
    }

    PlaylistModel::instance().loadPlaylists(playlistPtrs);
    PlaylistManager::instance().loadPlaylistNum(playlistNum);
}

void SettingsManager::readFileFolderMap()
{
    QSettings settings;
    settings.beginGroup("folderFileMap");

    QHash<QString, QStringList> folderFileMap;



    // Iterate through all keys (folder paths) in the settings group
    QStringList folderHashes = settings.childKeys();

    qDebug() << "folder file map keys" << folderHashes;

    for (const QString &folderHash : folderHashes) {
        QString folderPath = settings.value(folderHash + "_path").toString();
        QString fileListString = settings.value(folderHash).toString();

        // Split the stored string back into a list of files
        QStringList files = fileListString.split("%10", Qt::SkipEmptyParts);

        // Store in the QHash
        folderFileMap.insert(folderPath, files);
    }


    FolderView::instance().setFolderDirHash(folderFileMap);
    settings.endGroup();

}

void SettingsManager::readPlaylistCovers()
{
    QSettings settings;
    settings.beginGroup("playlistCovers");


}

void SettingsManager::removeFolder(QString &folderPath)
{
    //need to remove the entry in hashmap too in folderview.cpp
    QSettings settings;
    settings.sync(); //committing all changes

    //FolderView::instance().removeFolderFromMap(folderPath);

    QList<Folder> folders = settings.value("foldersToScan").value<QList<Folder>>();

    for(int i=0; i<folders.count();i++){
        if(folders[i].getFolderPath() == folderPath){
            folders.removeAt(i);
        }
    }

    settings.setValue("foldersToScan", QVariant::fromValue(folders));

}

QHash<QString, QStringList> SettingsManager::getFolderFileMap()
{
    return loadedFileFolderMap;
}

void SettingsManager::saveNowPlaying()
{
    //only need to store song id
    QList<std::shared_ptr<QueueEntry>> queue = NowPlaying::instance().getNowPlaying();
    QList<std::shared_ptr<QueueEntry>> played_songs = NowPlaying::instance().getPlayedSongs();

    qint64 position = MediaPlayerController::instance().position();

    QList<int> queue_IDs;
    QList<int> played_IDs;

    for(auto &queue_entry : queue){
        queue_IDs << queue_entry->songID;
    }

    for(auto &played_entry : played_songs){
        played_IDs << played_entry->songID;
    }

    QSettings settings;
    settings.beginGroup("nowPlaying");

    settings.setValue("queue", QVariant::fromValue(queue_IDs));
    settings.setValue("queueHistory", QVariant::fromValue(played_IDs));
    settings.setValue("nowPlayingSongPosition", QVariant::fromValue(position));
    settings.setValue("lastQueueID", NowPlaying::instance().queueModel()->getLastQueueID());

    settings.endGroup();
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

void SettingsManager::savePlaylists()
{
    //saves playlists and the playlistNum, since playlistNum is used as the id, this prevents duplicate playlists ids;
    QSettings settings;
    QList<std::shared_ptr<Playlist>> playlists = PlaylistModel::instance().getPlaylists();
    int playlistNum = PlaylistManager::instance().getPlaylistNum();
    QList<Playlist> playlistObj;

    for(const auto &playlist : playlists){
        playlistObj.append(*playlist);
    }

    settings.setValue("playlists", QVariant::fromValue(playlistObj));
    settings.setValue("playlistNum", playlistNum);
}

void SettingsManager::saveFileFolderMap()
{
    QSettings settings;

    //remove the current info since the saved folders may have been removed in main program
    settings.remove("folderFileMap");
    settings.sync();
    settings.beginGroup("folderFileMap");

    QHash<QString, QStringList> folderFileMap = FolderView::instance().getFolderFileMap();

    for (auto it = folderFileMap.begin(); it != folderFileMap.end(); ++it) {
        QString folderPath = it.key();
        QStringList files = it.value();

        QString fileListString = files.join("%10");
        QString key = QString::number(qHash(folderPath));
        qDebug() << "writing folder" << folderPath << "to file";

        //keys in qsettings cannot contain forward or backslahes so will store hash

        // Join files into a single comma-separated string

        // Save the folder path and corresponding file list
        settings.setValue(key, fileListString);
        settings.setValue(key + "_path", folderPath);
    }

    settings.endGroup();
}

void SettingsManager::savePlaylistCovers()
{
    QSettings settings;
    settings.remove("playlistCovers");
    settings.sync();
    settings.beginGroup("playlistCovers");

    QHash<int, QPixmap> playlistCovers = PlaylistImageProvider::instance().getCovers();

    for(auto it = playlistCovers.begin(); it != playlistCovers.end(); ++it){
        int coverKey = it.key();
        QPixmap coverArt = it.value();

        settings.setValue(QString::number(coverKey), coverArt);
    }

    settings.endGroup();
}



void SettingsManager::shutDown()
{
    saveNowPlaying();
    saveSongs();
    saveCoverArts();
    saveFileFolderMap();
    saveFolders();
    savePlaylists();
    savePlaylistCovers();
}















