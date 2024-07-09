#include "musicscannerthread.h"

MusicScannerThread::MusicScannerThread(QUrl musicPath,  CoverArtHolder *coverArtHolder, QObject *parent)
    : QThread{parent}, musicPath(musicPath), coverArtHolder(coverArtHolder)
{}

void MusicScannerThread::run() {
    QString localPath = musicPath.toLocalFile();

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

        if(!f.isNull() && !f.tag()->isEmpty()){
            songCount++;

            QString title = QString::fromUtf8(f.tag()->title().to8Bit(true));
            QString genre = QString::fromUtf8(f.tag()->genre().to8Bit(true));
            QString artists = QString::fromUtf8(f.tag()->artist().to8Bit(true));
            QString albumName = QString::fromUtf8(f.tag()->album().to8Bit(true));
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

            if(!coverArtHolder->hasCover(leadingArtist, albumName)){
                TagLib::VariantMap imgData = f.complexProperties("PICTURE").front();
                TagLib::ByteVector coverArt = imgData.value("data").toByteVector();
                QByteArray loadedCover = QByteArray(coverArt.data(), coverArt.size());
                coverArtHolder->addCover(leadingArtist, albumName, loadedCover);
            }

            std::shared_ptr<Song> song = std::make_shared<Song>(filePath, title, leadingArtist, albumName, genre, features, albumArtists, year, length, trackNum);

            //need to add the song to the listmodel, and the album
            emit songFetched(song);
       }



//        if(f.hasID3v2Tag()){

//            QStringList features;
//            QStringList albumArtists;
//            QString leadingArtist;
//            QByteArray loadedCover;
//            bool hasCover = false;

//            songCount++;

//            QString title = QString::fromStdWString(f.ID3v2Tag()->title().toWString());
//            QString genre = QString::fromStdWString(f.ID3v2Tag()->genre().toWString());
//            QString albumName = QString::fromStdWString(f.ID3v2Tag()->album().toWString());
//            int year = f.ID3v2Tag()->year();
//            int length = f.audioProperties()->lengthInSeconds();
//            int trackNum = f.ID3v2Tag()->track();

//            qDebug() << "Length of" << title << "is" << length << "seconds";

//            TagLib::PropertyMap props = f.properties();
//            TagLib::StringList artistList = props["ARTIST"];
//            bool firstIter = true;

//            for (const auto &artist : artistList){
//                QString feature = QString::fromStdWString(artist.toWString());

//                if(firstIter){
//                    leadingArtist = feature;
//                    firstIter = false;
//                }
//                else{
//                    qDebug() << "Featuring Artist:" << feature;
//                    features << feature;
//                }
//            }

//            TagLib::StringList albumArtistList = props["ALBUMARTIST"];
//            for(const auto &albumArtist : albumArtistList){
//                albumArtists << QString::fromStdWString(albumArtist.toWString());
//            }

//            if(albumArtists.isEmpty())
//                albumArtists << leadingArtist;


//            if(!coverArtHolder->hasCover(leadingArtist, albumName)){
//                TagLib::ID3v2::FrameList l = f.ID3v2Tag()->frameListMap()["APIC"];
//                if(!l.isEmpty()){
//                    auto *picFrame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(l.front());
//                    if(picFrame){
//                        loadedCover = QByteArray(picFrame->picture().data(), picFrame->picture().size());

//                        if(!loadedCover.isNull()){
//                            hasCover = true;
//                        }
//                    }
//                }
//            }



//            qDebug() << title << leadingArtist << "feat" << features << "on" << albumName;
//            qDebug() << filePath;

//            Song song(filePath, title, leadingArtist, albumName, features, length, trackNum);
//            songHolder->addSong(song);

//            if(hasCover){
//                coverArtHolder->addCover(leadingArtist, albumName, loadedCover);
//            }

//            if(albumHolder->isExists(albumName, albumArtists)){
//                albumHolder->addSongToAlbum(filePath, albumName, albumArtists);
//            }

//            else{
//                Album album(albumName, albumArtists, genre, year);
//                albumHolder->addAlbum(album);
//                albumHolder->addSongToAlbum(filePath, albumName, albumArtists);
//            }
//        }
    }

    emit scanningFinished(folderName, localPath, songCount);


}
