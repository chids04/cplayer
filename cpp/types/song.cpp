#include "song.h"


#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>


Song::Song(QObject *parent) : QObject(parent)
{}

Song::Song(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre,
           const QStringList &featuringArtists, const QStringList &albumArtists, int year, int length, int trackNum, int id,
           QObject *parent)
    : QObject(parent),
    m_filePath(filePath),
    m_title(title),
    m_artist(artist),
    m_album(album),
    m_genre(genre),
    m_albumArtists(albumArtists),
    m_featuringArtists(featuringArtists),
    m_length(length),
    m_trackNum(trackNum),
    m_year(year),
    m_id(id) {}

void Song::updateFile(const QString &coverPath)
{
#if defined(Q_OS_WIN)
        std::wstring encodedPath = m_filePath.toStdWString();
    TagLib::FileRef f(encodedPath.c_str(), TagLib::AudioProperties::Fast);
#else
        QByteArray temp = m_filePath.toUtf8();
    const char* encodedPath = temp.constData();
    TagLib::FileRef f(encodedPath, TagLib::AudioProperties::Fast);
#endif

    auto t = f.tag();

    t->setTitle(TagLib::String(m_title.toStdWString()));

    if(m_featuringArtists.size() == 0){
        t->setArtist(TagLib::String(m_artist.toStdWString()));
    }
    else{
        QString join_artists = m_artist + " / " + m_featuringArtists.join(" / ");
    }

    t->setAlbum(TagLib::String(m_album.toStdWString()));
    t->setGenre(TagLib::String(m_genre.toStdWString()));
    t->setYear(m_year);
    t->setTrack(m_trackNum);

    TagLib::StringList newArtists;

    for(auto &artist: m_albumArtists){
        newArtists.append(TagLib::String(artist.toStdWString()));
    }

    auto map = t->properties();
    map.replace("ALBUMARTIST", newArtists);


}

SongData Song::toSongData() const {
    return SongData(m_filePath, m_title, m_artist, m_album, m_genre, m_albumArtists, m_featuringArtists, m_length, m_trackNum, m_year, m_id);
}

void Song::fromSongData(const SongData &data) {
    m_filePath = data.filePath;
    m_title = data.title;
    m_artist = data.artist;
    m_album = data.album;
    m_genre = data.genre;
    m_albumArtists = data.albumArtists;
    m_featuringArtists = data.featuringArtists;
    m_length = data.length;
    m_trackNum = data.trackNum;
    m_year = data.year;
    m_id = data.id;
}
