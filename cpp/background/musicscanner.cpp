#include "musicscanner.h"
#include "coverimgprovider.h"

#include <QDebug>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QImage>
#include <QBuffer>

// TagLib includes
#include <qnamespace.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>


MusicScanner::MusicScanner(CoverImgProvider *coverImgProvider, QObject *parent)
    : QObject(parent), coverImgProvider(coverImgProvider)
{
    QSettings settings;
    id = settings.value("lastSongID", 0).toInt();
}

void MusicScanner::onFileRecieved(const QString &localPath)
{
#if defined(Q_OS_WIN)
    std::wstring encodedPath = localPath.toStdWString();
    TagLib::FileRef f(encodedPath.c_str(), TagLib::AudioProperties::Fast);
#else
    QByteArray temp = localPath.toUtf8();
    const char* encodedPath = temp.constData();
    TagLib::FileRef f(encodedPath, TagLib::AudioProperties::Fast);
#endif

    if(!f.isNull() && !f.tag()->isEmpty()){
        QFileInfo fileInfo(localPath);

#if defined(Q_OS_WIN)
        QString title = QString::fromStdWString(f.tag()->title().toWString());
        QString artists = QString::fromStdWString(f.tag()->artist().toWString());
        QString albumName = QString::fromStdWString(f.tag()->album().toWString());
#else
        QString title = QString::fromUtf8(f.tag()->title().to8Bit(true));
        QString artists = QString::fromUtf8(f.tag()->artist().to8Bit(true));
        QString albumName = QString::fromUtf8(f.tag()->album().to8Bit(true));
#endif
        QString genre = QString::fromUtf8(f.tag()->genre().to8Bit(true));
        int year = f.tag()->year();
        int length = 0; // Optionally use f.audioProperties()->lengthInSeconds();
        int trackNum = f.tag()->track();

        TagLib::PropertyMap properties = f.properties();
        QStringList features;
        QString leadingArtist;

        auto splitArtists = [](const QString &artists, QString &leadingArtist, QStringList &features) {
            QStringList parts = artists.split('/', Qt::SkipEmptyParts);
            for (int i = 0; i < parts.size(); ++i)
                parts[i] = parts[i].trimmed();
            if (!parts.isEmpty()) {
                leadingArtist = parts.first();
                if (parts.size() > 1)
                    features = parts.mid(1);
            } else {
                leadingArtist = artists.trimmed();
            }
        };

        splitArtists(artists, leadingArtist, features);

        QStringList albumArtists;
        TagLib::StringList albumArtistsList = properties["ALBUMARTIST"];
        for (const auto &albumArtist : albumArtistsList) {
            albumArtists << QString::fromStdWString(albumArtist.toWString());
        }
        if (albumArtists.isEmpty())
            albumArtists << leadingArtist;

        if (albumName.isEmpty())
            albumName = fileInfo.fileName();

        if (albumArtists == QStringList())
            albumArtists = QStringList(fileInfo.fileName());

        if (!coverImgProvider->hasCover(albumArtists, albumName)) {
            TagLib::VariantMap imgData = f.complexProperties("PICTURE").front();
            TagLib::ByteVector coverArt = imgData.value("data").toByteVector();
            QByteArray loadedCover(coverArt.data(), coverArt.size());
            coverImgProvider->addCover(albumArtists, albumName, loadedCover);
        }

        emit songDataFetched(localPath, title, leadingArtist, albumName, genre,
                              features, albumArtists, year, length, trackNum, id);
        id++;
    }
    else {
        if(!f.isNull()){
            if(f.tag()->isEmpty()){
                QFileInfo fi(localPath);
                emit songDataFetched(localPath, fi.fileName(), QString(), fi.fileName(),
                                    QString(), QStringList(), QStringList(fi.fileName()),
                                    int(), int(), int(), id);
                id++;
            }
        }
        
    }
}

void MusicScanner::scanDirectory(const QString &folderPath)
{
    QDir dir(folderPath);
    // Take a snapshot of the directory's contents (files & folders, excluding . and ..)
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    bool hasSubDirs = false;
    
    // Local map for grouping MP3 files based on album presence in folder name.
    std::unordered_map<QString, QStringList> localMap;

    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            // If it's a subdirectory, scan it recursively.
            hasSubDirs = true;
            scanDirectory(entry.absoluteFilePath());
            
        }
        else if (entry.isFile() && entry.suffix().toLower() == "mp3") {
            m_songCount++;
            QString filePath = entry.absoluteFilePath();

            // Parse the MP3 file using TagLib.
#if defined(Q_OS_WIN)
            std::wstring encodedPath = filePath.toStdWString();
            TagLib::FileRef f(encodedPath.c_str(), TagLib::AudioProperties::Fast);
#else
            QByteArray temp = filePath.toUtf8();
            const char* encodedPath = temp.constData();
            TagLib::FileRef f(encodedPath, TagLib::AudioProperties::Fast);
#endif

            if(!f.isNull() && !f.tag()->isEmpty()){
                // Extract album name.
                auto t = f.tag();

//win and unix handle special characters differently so need to use different methods to convert to QString
#if defined(Q_OS_WIN)
                QString albumName = QString::fromStdWString(t->album().toWString());
                QString title = QString::fromStdWString(t->title().toWString());
                QString artists = QString::fromStdWString(t->artist().toWString());
#else
                QString albumName = QString::fromUtf8(t->album().to8Bit(true));
                QString title = QString::fromUtf8(t->title().to8Bit(true));
                QString artists = QString::fromUtf8(t->artist().to8Bit(true));
#endif

                QString genre = QString::fromUtf8(t->genre().to8Bit(true));
                int year = t->year();
                int length = 0;
                int trackNum = t->track();
                TagLib::PropertyMap properties = f.properties();

                QStringList features;
                QString leadingArtist;

                auto splitArtists = [](const QString &artists, QString &leadingArtist, QStringList &features) {
                    QStringList parts = artists.split('/', Qt::SkipEmptyParts);
                    for (int i = 0; i < parts.size(); ++i)
                        parts[i] = parts[i].trimmed();
                    if (!parts.isEmpty()) {
                        leadingArtist = parts.first();
                        if (parts.size() > 1)
                            features = parts.mid(1);
                    } else {
                        leadingArtist = artists.trimmed();
                    }
                };
                splitArtists(artists, leadingArtist, features);


                QStringList albumArtists;

                TagLib::StringList albumArtistsList = properties["ALBUMARTIST"];
                for (const auto &albumArtist : albumArtistsList) {

                    QString artist = QString::fromStdWString(albumArtist.toWString());

                    if(artist.contains(',')){
                        QStringList artists_list = artist.split(',', Qt::SkipEmptyParts);
                        albumArtists.append(artists_list);
                    }
                    else{
                        albumArtists << artist;
                    }

                }

                if (albumArtists.isEmpty())
                    albumArtists << leadingArtist;

                if (albumName.isEmpty())
                    albumName = entry.fileName();

                if (albumArtists == QStringList())
                    albumArtists = QStringList(entry.fileName());
                if (albumName.isEmpty())
                    albumName = entry.fileName();


                // Check if the current folder name (dir.dirName()) contains  the album name (case-insensitive).
                if (dir.dirName().contains(albumName, Qt::CaseInsensitive)) {
                    localMap[folderPath].push_back(filePath);

                    //can also check if a cover.jpg exists the in the current directory and this can be used as the cover art instead
                    QString coverPath = dir.absoluteFilePath("cover.jpg"); 

                    
                    if(!coverImgProvider->hasCover(albumArtists, albumName)){

                        if(QFileInfo::exists(coverPath)){
                            QFile coverFile(coverPath);

                            coverFile.open(QIODevice::ReadOnly);
                            QByteArray coverArray = coverFile.readAll();

                            if(!coverArray.isNull()){
                                coverImgProvider->addCover(albumArtists, albumName, coverArray);
                            }

                            coverFile.close();
                        }
                    }

                }

                // extract cover art from the mp3 file if no cover.jpg found
                // could make this an option in settings

                if (!coverImgProvider->hasCover(albumArtists, albumName)) {
                    TagLib::VariantMap imgData = f.complexProperties("PICTURE").front();
                    TagLib::ByteVector coverArt = imgData.value("data").toByteVector();
                    QByteArray loadedCover(coverArt.data(), coverArt.size());

                    QImage image(loadedCover);

                    if(!image.isNull()){
                        coverImgProvider->addCover(albumArtists, albumName, loadedCover);
                    }

                }

                if (title.isEmpty())
                    title = entry.fileName();

                emit songDataFetched(filePath, title, leadingArtist, albumName, genre,
                                      features, albumArtists, year, length, trackNum, id);
                id++;
            }
            else {
                if(f.tag()->isEmpty()){
                    QFileInfo fi(filePath);
                    emit songDataFetched(filePath, fi.fileName(), QString(), fi.fileName(),
                                          QString(), QStringList(), QStringList(fi.fileName()),
                                          int(), int(), int(), id);
                    id++;
                }
            }
        }
    } // end for each entry

    // If localMap has entries, append it to the overall albumFoldersList.
    if (!localMap.empty()) {
        albumFoldersList.append(localMap);
    }

    
}



void MusicScanner::onFolderRecieved(const QUrl &folderUrl)
{
    m_songCount = 0;
    QString folderPath = folderUrl.toLocalFile();
    // Clear previous album folder snapshots.
    albumFoldersList.clear();
    // Start the recursive directory snapshot scan.
    scanDirectory(folderPath);
    // Emit the current song ID for persistence.
    QDir dir(folderPath);

    emit scanningFinished(dir.dirName(), folderPath, m_songCount);
    emit saveID(id);
}
