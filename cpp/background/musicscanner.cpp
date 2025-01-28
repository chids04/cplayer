#include "musicscanner.h"

#include <QDebug>
#include <QSettings>
#include <QPixmap>
#include <QFileInfo>
#include <QStringList>
#include <QDirIterator>

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
            //int length = f.audioProperties()->lengthInSeconds();
            int length = 0;
            int trackNum = f.tag()->track();


            TagLib::PropertyMap properties = f.properties();

            QStringList features;
            QString leadingArtist;

            auto splitArtists = [](const QString &artists, QString &leadingArtist, QStringList &features){
                if(artists.contains(" / ")){
                    QStringList artistList = artists.split(" / ");
                    leadingArtist = artistList.first();
                    features = artistList.mid(1);
                }
                else{
                    leadingArtist = artists;
                }
            };

            splitArtists(artists, leadingArtist, features);

            QStringList albumArtists;
            TagLib::StringList albumArtistsList = properties["ALBUMARTIST"];

            for(const auto &albumArtist : albumArtistsList){
                albumArtists << QString::fromStdWString(albumArtist.toWString());
            }

            if(albumArtists.isEmpty()){
                albumArtists << leadingArtist;
            }

            if(albumArtists.isEmpty()){
                albumArtists << leadingArtist;
            }

            if(albumName == ""){
                albumName = fileInfo.fileName();
            }

            if(albumArtists == QStringList()){
                albumArtists = QStringList(fileInfo.fileName());
            }

            if(!coverImgProvider->hasCover(albumArtists, albumName)){
                TagLib::VariantMap imgData = f.complexProperties("PICTURE").front();
                TagLib::ByteVector coverArt = imgData.value("data").toByteVector();
                QByteArray loadedCover = QByteArray(coverArt.data(), coverArt.size());
                coverImgProvider->addCover(albumArtists, albumName, loadedCover);
            }

            emit songDataFetched(localPath, title, leadingArtist, albumName, genre, features, albumArtists, year, length, trackNum, id);
            id++;

        }else{
            if(f.tag()->isEmpty()){
                QFileInfo fi(localPath);
                emit songDataFetched(localPath, fi.fileName(), QString(), fi.fileName(), QString(), QStringList(), QStringList(fi.fileName()), int(), int(), int(), id);
                id++;
            }
        }


}

void MusicScanner::onFolderRecieved(const QUrl &folderPath)
{
    QString localPath = folderPath.toLocalFile();

    QFileInfo fileInfo(localPath);
    QString folderName = fileInfo.fileName();
    int songCount = 0;

    QDirIterator it(localPath, QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);

    while(it.hasNext()){
        QString filePath = it.next();

#if defined(Q_OS_WIN)
        std::wstring encodedPath = filePath.toStdWString();
        TagLib::FileRef f(encodedPath.c_str(), TagLib::AudioProperties::Fast);
#else
        QByteArray temp = filePath.toUtf8();
        const char* encodedPath = temp.constData();
        TagLib::FileRef f(encodedPath, TagLib::AudioProperties::Fast);
#endif

        songCount++;
        if(!f.isNull() && !f.tag()->isEmpty()){



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
            //int length = f.audioProperties()->lengthInSeconds();
            int length = 0;
            int trackNum = f.tag()->track();


            TagLib::PropertyMap properties = f.properties();

            QStringList features;
            QString leadingArtist;

            auto splitArtists = [](const QString &artists, QString &leadingArtist, QStringList &features){
                if(artists.contains("/") || artists.contains(" / ")){
                    QStringList artistList;

                    //some programs (deemix) put all artists into artist string
                    if(artists.contains("/")){
                        artistList = artists.split("/");
                    }
                    else if(artistList.contains(" / ")){
                        artistList = artists.split(" / ");
                    }

                    leadingArtist = artistList.first();
                    features = artistList.mid(1);
                }
                else{
                    leadingArtist = artists;
                }
            };

            splitArtists(artists, leadingArtist, features);

            QStringList albumArtists;
            TagLib::StringList albumArtistsList = properties["ALBUMARTIST"];

            for(const auto &albumArtist : albumArtistsList){
                albumArtists << QString::fromStdWString(albumArtist.toWString());
            }

            if(albumArtists.isEmpty()){
                albumArtists << leadingArtist;
            }

            if(albumName == ""){
                albumName = fileInfo.fileName();
            }

            if(albumArtists == QStringList()){
                albumArtists = QStringList(fileInfo.fileName());
            }

            if(!coverImgProvider->hasCover(albumArtists, albumName)){
                TagLib::VariantMap imgData = f.complexProperties("PICTURE").front();
                TagLib::ByteVector coverArt = imgData.value("data").toByteVector();
                QByteArray loadedCover = QByteArray(coverArt.data(), coverArt.size());
                coverImgProvider->addCover(albumArtists, albumName, loadedCover);
            }

            if(title == ""){
                title = fileInfo.fileName();
            }

            emit songDataFetched(filePath, title, leadingArtist, albumName, genre, features, albumArtists, year, length, trackNum, id);
            id++;

        }
        else{
            //here is for where songs has no metatdata
            if(f.tag()->isEmpty()){
                QFileInfo fi(filePath);
                emit songDataFetched(filePath, fi.fileName(), QString(), fi.fileName(), QString(), QStringList(), QStringList(fi.fileName()), int(), int(), int(), id);
                id++;
            }

        }
    }


    emit scanningFinished(folderName, localPath, songCount);
    emit saveID(id);
}

