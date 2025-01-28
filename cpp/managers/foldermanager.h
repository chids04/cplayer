#ifndef FOLDERMANAGER_H
#define FOLDERMANAGER_H

#include <QObject>
#include <QUrl>
#include <QFileSystemWatcher>
#include <QHash>
#include <QThread>

#include "folderlistmodel.h"
#include "songmanager.h"
#include "coverimgprovider.h"


class FolderManager : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathChanged);
    Q_PROPERTY(FolderListModel *folderListModel READ folderListModel WRITE setFolderListModel NOTIFY folderListModelChanged)
public:

    explicit FolderManager(SongManager *songManager, CoverImgProvider *coverProvider, QObject *parent = nullptr);

    ~FolderManager(){
        workerThread.quit();
        workerThread.wait();
    }

    QUrl path() const;
    void addToWatcher(const QString &path);
    void setPath(const QUrl &newPath);
    void setFolderDirHash(const QHash<QString, QStringList> &loadedFileFolderHash);
    void addFilesToFolder(const QString &folderPath, const QStringList &newFiles);
    void removeFilesFromFolder(const QString &folderPath, const QString &fileName);
    void removeFolderFromMap(const QString &folderPath);
    void saveToSettings();
    void loadFromSettings();
    QStringList getFilesInFolder(const QString &folderPath);
    QHash<QString,QStringList> getFolderFileMap();

    FolderListModel *folderListModel() const;
    void folderListModel(FolderListModel *newFolderListModel);

    void setFolderListModel(FolderListModel *newFolderListModel);

    void setSongListModel(SongListModel *newSongListModel);

    void setCoverProvider(CoverImgProvider *newCoverProvider);

signals:
    void onSongsLoaded();
    void pathChanged();
    void deleteSongs(const QString &folderPath);
    void deleteAlbums();
    void scanFile(const QString &filePath);
    void scanFolder(const QUrl &folderPath);
    void songFetched(Song *song);
    void folderListModelChanged();

public slots:
    void startFolderScanningThread(const QUrl &filePath, bool firstScan);
    void onScanningFinished(const QString &folderName, const QString &folderPath, int songCount);
    void removeFolder(int index, const QString &folderPath);

private slots:
    void onFileChanged(const QString &path);
    void onDirectoryChanged(const QString &path);
    void onSaveID(int id);

    void onSongDataFetched(const QString &filePath, const QString &title, const QString &artist,
                           const QString &album, const QString &genre, const QStringList &featuringArtists,
                           const QStringList &albumArtists, int year, int length, int trackNum, int id);

private:
    QUrl m_path;
    QFileSystemWatcher fsWatch;
    QHash<QString, QStringList> folderDirHash;

    void appendToFile(QUrl &folderPath);
    void readFromFile(QUrl &filePath);

    bool isScanning = false;
    QThread workerThread;

    FolderListModel *m_folderListModel;
    SongListModel *songListModel;
    CoverImgProvider *coverProvider;
    int lastSongID = 0;
};

#endif // FOLDERMANAGER_H
