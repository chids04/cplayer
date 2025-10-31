#include "songmanager.h"
#include "coverimgprovider.h"

#include <qdebug.h>
#include <qurl.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>
#include <tbytevector.h>

SongManager::SongManager(PlaybackManager *playbackManager, QObject *parent)
{
    //load songlistmodel from settings here
    //load albums from settings
    albumListModel = new AlbumListModel;

    songListModel = new SongListModel(albumListModel, playbackManager->mediaPlayer(), playbackManager->nowPlaying());

    mediaPlayer = playbackManager->mediaPlayer();

    //these models exposed to qml
    SongFilterProxyModel *songFilterProxyModel = new SongFilterProxyModel(songListModel);
    AlbumFilterProxyModel *albumFilterProxyModel = new AlbumFilterProxyModel(songListModel);
    AlbumSearchFilter *albumSearchFilter = new AlbumSearchFilter(albumListModel);

    setSongModel(songFilterProxyModel);
    setAlbumSongsModel(albumFilterProxyModel);
    setAlbumSearchModel(albumSearchFilter);

    setFeaturesList(new QStringListModel);
    setAlbumArtistsList(new QStringListModel);

}

void SongManager::init(PlaylistManager *playlistManager, CoverImgProvider *coverImgProvider)
{
    //avoids circular dependency
    connect(songListModel, &SongListModel::removeFromPlaylist, playlistManager->playlistModel(), &PlaylistModel::removeSongs);
    coverArts = coverImgProvider;
}

void SongManager::loadFromSettings()
{
    songListModel->readSongs();
}

void SongManager::saveToSettings()
{
    songListModel->saveSongs();
}

SongFilterProxyModel *SongManager::songModel() const
{
    return m_songModel;
}

void SongManager::setSongModel(SongFilterProxyModel *newSongModel)
{
    if (m_songModel == newSongModel)
        return;
    m_songModel = newSongModel;
    emit songModelChanged();
}

AlbumFilterProxyModel *SongManager::albumSongsModel() const
{
    return m_albumSongsModel;
}

void SongManager::setAlbumSongsModel(AlbumFilterProxyModel *newAlbumSongsModel)
{
    if (m_albumSongsModel == newAlbumSongsModel)
        return;
    m_albumSongsModel = newAlbumSongsModel;
    emit albumSongsModelChanged();
}

AlbumSearchFilter *SongManager::albumSearchModel() const
{
    return m_albumSearchModel;
}

void SongManager::setAlbumSearchModel(AlbumSearchFilter *newAlbumSearchModel)
{
    if (m_albumSearchModel == newAlbumSearchModel)
        return;
    m_albumSearchModel = newAlbumSearchModel;
    emit albumSearchModelChanged();
}

Album* SongManager::currentAlbum() const
{
    return m_currentAlbum;
}


void SongManager::setCurrentAlbum(Album *newCurrentAlbum)
{
    m_currentAlbum = newCurrentAlbum;
    emit currentAlbumChanged();
}

SongListModel *SongManager::getSongListModel() const
{
    return songListModel;
}

AlbumListModel *SongManager::getAlbumListModel() const
{
    return albumListModel;
}

void SongManager::setAlbum(Album *album)
{
    setCurrentAlbum(album);
    setAlbumName(album->getName());
    setAlbumArtists(album->getArtist());
    setAlbumYear(album->getYear());
    setAlbumGenre(album->getGenre());

    m_albumSongsModel->setCurrentAlbumName(album->getName());
}

void SongManager::insertFeature(const QString &feature)
{
    if(m_featuresList->insertRow(m_featuresList->rowCount())){
        QModelIndex index = m_featuresList->index(m_featuresList->rowCount() - 1);
        m_featuresList->setData(index, feature);
    }
}

void SongManager::setFeaturesToEdit(const QStringList &features)
{
    m_featuresList->setStringList(features);
}

void SongManager::moveFeature(int src, int dst)
{
    m_featuresList->moveRows(QModelIndex(), src, 1, QModelIndex(), dst);

}

void SongManager::removeFeature(int index)
{
    m_featuresList->removeRows(index, 1, QModelIndex());
}

void SongManager::insertArtist(const QString &artist)
{
    if(m_albumArtistsList->insertRow(m_albumArtistsList->rowCount())){
        QModelIndex index = m_albumArtistsList->index(m_albumArtistsList->rowCount() - 1);
        m_albumArtistsList->setData(index, artist);
    }
}

void SongManager::setAlbumArtistsToEdit(const QStringList &albumArtists)
{
    m_albumArtistsList->setStringList(albumArtists);
}

void SongManager::moveArtist(int src, int dst)
{
    m_albumArtistsList->moveRows(QModelIndex(), src, 1, QModelIndex(), dst);
}

void SongManager::removeArtist(int index)
{
    m_albumArtistsList->removeRows(index, 1, QModelIndex());
}


void SongManager::saveChanges(Song* song, const QString &title, const QString &leadingArtist, const QString &album,
                              const QString &genre, int year, int trackNum, const QUrl &coverPath)
{

    QString filePath = song->m_filePath;

#if defined(Q_OS_WIN)
    std::wstring encodedPath = filePath.toStdWString();
    TagLib::FileRef f(encodedPath.c_str(), TagLib::AudioProperties::Fast);
#else
    QByteArray temp = filePath.toUtf8();
    const char* encodedPath = temp.constData();
    TagLib::FileRef f(encodedPath, TagLib::AudioProperties::Fast);
#endif

    if(f.isNull()){
        //SEND ERROR TO UI
        qDebug() << "error in opening file for editing";
        return;
    }

    if(coverPath != QUrl()){
        if(!coverPath.isValid()){
            //SEND ERROR TO UI
            qDebug() << "invalid coverPath";
            return;
        }
    }

    bool newAlbum = false;
    if(song->m_album != album){
        newAlbum = true;
    }

    song->m_trackNum = trackNum;
    song->m_title = title;
    song->m_artist = leadingArtist;
    song->m_album = album;
    song->m_featuringArtists = m_featuresList->stringList();
    song->m_albumArtists = m_albumArtistsList->stringList();
    song->m_genre = genre;
    song->m_year = year;

    songListModel->updateSong(song->m_id);
    mediaPlayer->updateSong(song);
    


    QString artistStr = leadingArtist;

    for (const auto& feature: song->m_featuringArtists){
        artistStr += "/" + feature.trimmed();
    }

    QString albumArtistStr = song->m_albumArtists.join('/');

/*
special characters handled differently on win and unix
*/
#if defined(Q_OS_WIN)
    std::wstring saved_title = title.toStdWString();
    std::wstring saved_artist = artistStr.toStdWString();
    std::wstring saved_albumArtists = albumArtistStr.toStdWString();
    std::wstring saved_album = album.toStdWString();
#else
    temp = artistStr.trimmed().toUtf8();
    const char* saved_artist = temp.constData();

    temp = title.trimmed().toUtf8();
    const char* saved_title = temp.constData();

    temp = albumArtistStr.toUtf8();
    const char* saved_albumArtists = temp.constData();

    temp = album.toUtf8();
    const char* saved_album = temp.constData();
#endif

    auto t = f.tag();
    t->setTitle(TagLib::String(saved_title));
    t->setArtist(TagLib::String(saved_artist));
    t->setTrack(trackNum);
    t->setAlbum(TagLib::String(saved_album));
    t->setGenre(TagLib::String(genre.toStdString()));

    auto map = t->properties();
    map.replace("ALBUMARTIST", TagLib::String(saved_albumArtists));


    QByteArray imageData;

    if(coverPath.isLocalFile()){
        QImage image = QImage(coverPath.toLocalFile());
        image = image.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "JPEG");
    }
    else if(coverPath.scheme() == "image"){
        imageData = coverArts->getCover(song->m_albumArtists, song->m_album);
        QImage temp = QImage::fromData(imageData);
        
        if(!temp.isNull()){
            temp = temp.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }

        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        temp.save(&buffer, "JPEG");
    }

    //dont need to pass size since image data returns null terminated char array
    TagLib::ByteVector img_bytes(imageData.constData());

    f.setComplexProperties("PICTURE", {
        {
            {"data", img_bytes},
            {"pictureType", "Front Cover"},
            {"mimeType", "image/jpeg"}
        }
    });

    bool success = f.save();

    if(success){
        //SEND TO UI
        qDebug() << "edited metadata succesfully";
    }
    
}

QString SongManager::albumName() const
{
    return m_albumName;
}

void SongManager::setAlbumName(const QString &newAlbumName)
{
    if (m_albumName == newAlbumName)
        return;
    m_albumName = newAlbumName;
    emit albumNameChanged();
}

QStringList SongManager::albumAritsts() const
{
    return m_albumArtists;
}

void SongManager::setAlbumArtists(const QStringList &newAlbumArtists)
{
    if (m_albumArtists == newAlbumArtists)
        return;
    m_albumArtists = newAlbumArtists;
    emit albumArtistsChanged();
}

QString SongManager::albumGenre() const
{
    return m_albumGenre;
}

void SongManager::setAlbumGenre(const QString &newAlbumGenre)
{
    if (m_albumGenre == newAlbumGenre)
        return;
    m_albumGenre = newAlbumGenre;
    emit albumGenreChanged();
}

int SongManager::albumYear() const
{
    return m_albumYear;
}

void SongManager::setAlbumYear(int newAlbumYear)
{
    if (m_albumYear == newAlbumYear)
        return;
    m_albumYear = newAlbumYear;
    emit albumYearChanged();
}

QStringListModel *SongManager::featuresList() const
{
    return m_featuresList;
}

void SongManager::setFeaturesList(QStringListModel *newFeaturesList)
{
    if (m_featuresList == newFeaturesList)
        return;
    m_featuresList = newFeaturesList;
    emit featuresListChanged();
}

QStringListModel *SongManager::albumArtistsList() const
{
    return m_albumArtistsList;
}

void SongManager::setAlbumArtistsList(QStringListModel *newAlbumArtistsList)
{
    if (m_albumArtistsList == newAlbumArtistsList)
        return;
    m_albumArtistsList = newAlbumArtistsList;
    emit albumAritstsListChanged();
}
