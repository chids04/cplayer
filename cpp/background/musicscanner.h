#ifndef MUSICSCANNER_H
#define MUSICSCANNER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QUrl>
#include <unordered_map>

// Forward declaration of CoverImgProvider
class CoverImgProvider;

class MusicScanner : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a MusicScanner.
     * @param coverImgProvider Pointer to a CoverImgProvider instance for cover art handling.
     * @param parent Optional parent QObject.
     */
    explicit MusicScanner(CoverImgProvider *coverImgProvider, QObject *parent = nullptr);



public slots:
    /**
     * @brief Initiates a recursive directory snapshot scan on the folder provided by URL.
     * @param folderPath The URL of the folder to scan.
     */
    void onFolderRecieved(const QUrl &folderPath);


    /**
     * @brief Processes a single music file.
     * @param localPath The absolute path to the music file.
     */
    void onFileRecieved(const QString &localPath);

signals:
    /**
     * @brief Emitted when a song's metadata has been fetched.
     * @param localPath The absolute path of the song file.
     * @param title The title of the song.
     * @param leadingArtist The primary artist.
     * @param albumName The album name.
     * @param genre The genre of the song.
     * @param features List of featured artists.
     * @param albumArtists List of album artists.
     * @param year The release year.
     * @param length The duration of the song.
     * @param trackNum The track number.
     * @param id A unique song identifier.
     */
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

    /**
     * @brief Emitted when scanning of a directory is finished.
     * @param folderName The name of the scanned folder.
     * @param localPath The absolute path of the scanned folder.
     * @param songCount The number of songs found in this folder.
     */
    void scanningFinished(const QString &folderName,
                          const QString &localPath,
                          int songCount);

    /**
     * @brief Emitted to save the current song ID for persistence.
     * @param id The next available song ID.
     */
    void saveID(int id);

private:
    CoverImgProvider *coverImgProvider;
    int id;
    int m_songCount = 0;

    // A list of unordered maps, where each map groups MP3 file paths by folder path.
    QList<std::unordered_map<QString, QStringList>> albumFoldersList;

    /**
     * @brief Recursively scans a directory using a snapshot approach.
     * For each subdirectory, a snapshot is taken. MP3 files are parsed and, if the current
     * folder's name contains the song's album name, the file is added to a grouping map.
     * @param folderPath The absolute path of the directory to scan.
     * @return the number of songs found in the directory.
     */
    int scanDirectory(const QString &folderPath);
};

#endif // MUSICSCANNER_H
