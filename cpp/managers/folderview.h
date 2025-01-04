#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QObject>
#include <QUrl>
#include <QFileSystemWatcher>
#include <QHash>
#include <QThread>


class FolderView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathChanged);
public:

    explicit FolderView(QObject *parent = nullptr);
    static FolderView &instance();

    ~FolderView(){
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
    QStringList getFilesInFolder(const QString &folderPath);
    QHash<QString,QStringList> getFolderFileMap();

signals:
    void onSongsLoaded();
    void pathChanged();
    void deleteSongs(QString &folderPath);
    void deleteAlbums();
    void scanFile(const QString &filePath);

public slots:
    void startFolderScanningThread(QUrl filePath, bool firstScan);
    void onScanningFinished(QString folderName, QString folderPath, int songCount);
    void removeFolder(int index, QString folderPath);

private slots:
    void onFileChanged(const QString &path);
    void onDirectoryChanged(const QString &path);

private:
    QUrl m_path;
    QFileSystemWatcher fsWatch;
    QHash<QString, QStringList> folderDirHash;

    void appendToFile(QUrl &folderPath);
    void readFromFile(QUrl &filePath);

    bool isScanning = false;
    QThread workerThread;
};

#endif // FOLDERVIEW_H
