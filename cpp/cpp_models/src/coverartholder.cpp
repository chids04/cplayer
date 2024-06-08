#include "coverartholder.h"

CoverArtHolder::CoverArtHolder() {}

void CoverArtHolder::addCover(const QString &artist, const QString &albumName, QByteArray &coverArt)
{
    CoverArtKey key = {artist, albumName};
    coverArts.insert(key, coverArt);


}

QByteArray CoverArtHolder::getCover(const QString &artist, const QString &albumName) const
{
    CoverArtKey key = {artist, albumName};

    if(coverArts.contains(key)){
        return coverArts.value(key);
    }
    return QByteArray();

}

bool CoverArtHolder::hasCover(const QString &artist, const QString &albumName) const
{
    CoverArtKey key = {artist, albumName};
    return coverArts.contains(key);
}

