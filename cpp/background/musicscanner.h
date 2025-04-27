#ifndef MUSICSCANNER_H
#define MUSICSCANNER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QUrl>
#include <unordered_map>

class CoverImgProvider;

class MusicScanner : public QObject
{
    Q_OBJECT
public:
    explicit MusicScanner(CoverImgProvider *coverImgProvider, QObject *parent = nullptr);

public slots:
    void onFolderRecieved(const QUrl &folderPath);


    void onFileRecieved(const QString &localPath);

signals:
    void songDataFetched(const QString &localPath,
        const QString &title,
        const QString &leadingArtist,
        const QString &albumName,
        const QString &genre,
        const QStringList &features,
        const QStringList &albumArtists,
        int year,
        int length,
        int trackNum,
        int id);

    void scanningFinished(const QString &folderName,
        const QString &localPath,
        int songCount);

    void saveID(int id);

private:
    CoverImgProvider *coverImgProvider;
    int id;
    int m_songCount = 0;

    // a list of unordered maps, where each map groups MP3 file paths by folder path.
    QList<std::unordered_map<QString, QStringList>> albumFoldersList;

    void scanDirectory(const QString &folderPath);
};

#endif // MUSICSCANNER_H
