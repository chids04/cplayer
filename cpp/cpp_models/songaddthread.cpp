#include "songaddthread.h"

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

#include "coverartholder.h"
#include "albumlistmodel.h"
#include "songlistmodel.h"

SongAdd::SongAdd(QObject *parent) : QObject(parent)
{
    QSettings settings;
    id = settings.value("lastSongID", 0).toInt();

}

void SongAdd::onFileRecieved(const QString &localPath)
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

            if(!CoverArtHolder::instance().hasCover(albumArtists, albumName)){
                TagLib::VariantMap imgData = f.complexProperties("PICTURE").front();
                TagLib::ByteVector coverArt = imgData.value("data").toByteVector();
                QByteArray loadedCover = QByteArray(coverArt.data(), coverArt.size());
                CoverArtHolder::instance().addCover(albumArtists, albumName, loadedCover);
            }

            std::shared_ptr<Song> song = std::make_shared<Song>(localPath, title, leadingArtist, albumName, genre, features, albumArtists, year, length, trackNum, id);
            id++;

            //need to add the song to the listmodel, and the album
            emit songFetched(song);
        }

    QSettings settings;
    settings.setValue("lastSongID", id);
}
