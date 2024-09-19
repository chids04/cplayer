#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QObject>
#include <QUrl>

#include "folderlistmodel.h"
#include "songlistmodel.h"
#include "albumlistmodel.h"
#include "musicscannerthread.h"
#include "coverartholder.h"

class FolderView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl path READ path WRITE setPath NOTIFY pathChanged);
public:

    explicit FolderView(QObject *parent = nullptr);
    static FolderView &instance();

    QUrl path() const;
    void setPath(const QUrl &newPath);

signals:
    void onSongsLoaded();

    void pathChanged();

public slots:
    void startFolderScanningThread(QUrl filePath);
    void onScanningFinished(QString folderName, QString folderPath, int songCount);
    void removeFolder(int index, QString folderPath);

private:
    QUrl m_path;

    void appendToFile(QUrl &folderPath);
    void readFromFile(QUrl &filePath);
};

#endif // FOLDERVIEW_H
