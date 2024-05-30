#include "musiclibrary.h"


MusicLibrary::MusicLibrary(SongListModel *model, CoverArtHolder *coverArtHolder, AlbumHolder *albumHolder, QObject *parent) : songModel(model), coverArtHolder(coverArtHolder), albumHolder(albumHolder), QObject(parent) {
    connect(this, &MusicLibrary::musicPathChanged, this, &MusicLibrary::onMusicPathChanged);

}

QUrl MusicLibrary::musicPath() const
{
    return m_musicPath;
}

void MusicLibrary::setMusicPath(const QUrl &newMusicPath)
{
    if (m_musicPath == newMusicPath)
        return;
    m_musicPath = newMusicPath;

    emit musicPathChanged(m_musicPath);
}

//support for mp3 files only, will create a class to manage this and support different filetypes
void MusicLibrary::onMusicPathChanged(const QUrl &dirPath){
    QString localPath = m_musicPath.toLocalFile();
    QDirIterator it(localPath, QStringList() << "*.mp3", QDir::Files, QDirIterator::Subdirectories);

    while(it.hasNext()){
        QString filePath = it.next();
        const char *encodedPath = QFile::encodeName(filePath).constData();

        //TagLib::FileRef f(filePath.toStdString().c_str());
        TagLib::MPEG::File f(encodedPath);

        if(f.hasID3v2Tag()){
            //TagLib::Tag *tag = f.tag();


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
            //loadedCover.loadFromData(QByteArray::fromRawData(l.front().data(), l.front()->size()))
            // QString title = QString::fromStdWString(tag->title().toWString());
            // QString albumName = QString::fromStdWString(tag->album().toWString());
            // QString genre = QString::fromStdWString(tag->genre().toWString());
            // int year = tag->year();

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


                        // TagLib::StringList names = f.complexPropertyKeys();
            // for(const auto &name : names){
            //     const auto& properties = f.complexProperties(name);
            //     for(const auto &property : properties){
            //         for(const auto &[key, value] : property){
            //             if(value.type() == TagLib::Variant::ByteVector){
            //                 loadedCover.loadFromData(QByteArray::fromRawData(value.value<TagLib::ByteVector>().data(),value.value<TagLib::ByteVector>().size()));
            //                 loadedCover = loadedCover.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            //             }
            //         }
            //     }
            // }



            qDebug() << title << leadingArtist << "feat" << features << "on" << albumName;
            qDebug() << filePath;

            Song song(filePath, title, leadingArtist, albumName, features, length, trackNum);
            songModel->addSong(song);

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

        albumHolder->printAlbums();
        albumHolder->addToModel();

}


// QQmlListProperty<Song> MusicLibrary::songsModel()
// {
//     return QQmlListProperty<Song>(this, nullptr, &MusicLibrary::songsCount, &MusicLibrary::songAt);
// }

// qsizetype MusicLibrary::songsCount(QQmlListProperty<Song> *list){
//     return reinterpret_cast<MusicLibrary *>(list->data)->songs.size();
// }

// Song* MusicLibrary::songAt(QQmlListProperty<Song> *list, qsizetype index){
//     return &(reinterpret_cast<MusicLibrary*>(list->data)->songs.at(index));
// }
