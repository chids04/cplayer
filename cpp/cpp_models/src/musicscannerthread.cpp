#include "musicscannerthread.h"

MusicScannerThread::MusicScannerThread(QUrl musicPath, SongHolder *songHolder, AlbumHolder *albumHolder, CoverArtHolder *coverArtHolder, QObject *parent)
    : QThread{parent}, musicPath(musicPath), songHolder(songHolder), albumHolder(albumHolder), coverArtHolder(coverArtHolder)
{

}

void MusicScannerThread::run() {

    QString localPath = musicPath.toLocalFile();
    QDirIterator it(localPath, QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);

    while(it.hasNext()){
        QString filePath = it.next();
        std::wstring encodedPath = filePath.toStdWString();
        TagLib::MPEG::File f(encodedPath.c_str());

        if(f.hasID3v2Tag()){

            QStringList features;
            QStringList albumArtists;
            QString leadingArtist;
            QByteArray loadedCover;
            bool hasCover = false;




            QString title = QString::fromStdWString(f.ID3v2Tag()->title().toWString());
            QString genre = QString::fromStdWString(f.ID3v2Tag()->genre().toWString());
            QString albumName = QString::fromStdWString(f.ID3v2Tag()->album().toWString());
            int year = f.ID3v2Tag()->year();
            int length = f.audioProperties()->lengthInSeconds();
            int trackNum = f.ID3v2Tag()->track();

            qDebug() << "Length of" << title << "is" << length << "seconds";

            TagLib::PropertyMap props = f.properties();
            TagLib::StringList artistList = props["ARTIST"];
            bool firstIter = true;

            for (const auto &artist : artistList){
                QString feature = QString::fromStdWString(artist.toWString());

                if(firstIter){
                    leadingArtist = feature;
                    firstIter = false;
                }
                else{
                    qDebug() << "Featuring Artist:" << feature;
                    features << feature;
                }
            }

            TagLib::StringList albumArtistList = props["ALBUMARTIST"];
            for(const auto &albumArtist : albumArtistList){
                albumArtists << QString::fromStdWString(albumArtist.toWString());
            }

            if(albumArtists.isEmpty())
                albumArtists << leadingArtist;


            if(!coverArtHolder->hasCover(leadingArtist, albumName)){
                TagLib::ID3v2::FrameList l = f.ID3v2Tag()->frameListMap()["APIC"];
                if(!l.isEmpty()){
                    auto *picFrame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(l.front());
                    if(picFrame){
                        loadedCover = QByteArray(picFrame->picture().data(), picFrame->picture().size());

                        if(!loadedCover.isNull()){
                            hasCover = true;
                        }
                    }
                }
            }



            qDebug() << title << leadingArtist << "feat" << features << "on" << albumName;
            qDebug() << filePath;

            Song song(filePath, title, leadingArtist, albumName, features, length, trackNum);
            songHolder->addSong(song);

            if(hasCover){
                coverArtHolder->addCover(leadingArtist, albumName, loadedCover);
            }

            if(albumHolder->isExists(albumName, albumArtists)){
                albumHolder->addSongToAlbum(filePath, albumName, albumArtists);
            }

            else{
                Album album(albumName, albumArtists, genre, year);
                albumHolder->addAlbum(album);
                albumHolder->addSongToAlbum(filePath, albumName, albumArtists);
            }
        }
    }

    emit scanningFinished();


}
