#include "coverartholder.h"

#include <QSettings>

CoverArtHolder::CoverArtHolder() {}

CoverArtHolder &CoverArtHolder::instance()
{
    static CoverArtHolder coverArtHolder;
    return coverArtHolder;
}

void CoverArtHolder::addCover(const QStringList &artists, const QString &albumName, QByteArray &coverArt)
{
    CoverArtKey key = {artists, albumName};
    coverArts.insert(key, coverArt);


}

QByteArray CoverArtHolder::getCover(const QStringList &artists, const QString &albumName) const
{
    CoverArtKey key = {artists, albumName};

    if(coverArts.contains(key)){
        return coverArts.value(key);
    }
    return QByteArray();

}

bool CoverArtHolder::hasCover(const QStringList &artists, const QString &albumName) const
{
    CoverArtKey key = {artists, albumName};
    return coverArts.contains(key);
}

void CoverArtHolder::loadFromSettings() {
    QSettings settings;
    settings.beginGroup("CoverArts");

    QStringList keys = settings.childKeys();
    for (const QString &key : keys) {
        CoverArtKey coverKey = CoverArtKey::fromString(key);  // Convert string back to CoverArtKey
        QByteArray coverArt = settings.value(key).toByteArray();
        coverArts.insert(coverKey, coverArt);  // Insert into the QHash
    }

    settings.endGroup();
}

QHash<CoverArtKey, QByteArray> CoverArtHolder::getAllCovers()
{
    return coverArts;
}

