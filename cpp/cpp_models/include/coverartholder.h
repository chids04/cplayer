#ifndef COVERARTHOLDER_H
#define COVERARTHOLDER_H

#include <QUrl>
#include <QHash>
#include <QDebug>
#include <QString>
#include <QPixmap>
#include <QByteArray>
#include <QStringList>

struct CoverArtKey{
    QString artist;
    QString albumName;

    bool operator==(const CoverArtKey &other) const {
        return artist == other.artist && albumName == other.albumName;
    }
};

//simple hashing function
inline uint qHash(const CoverArtKey &key, uint seed = 0){
    return qHash(key.artist, seed) ^ qHash(key.albumName, seed);
}

class CoverArtHolder
{

public:
    CoverArtHolder();
    static CoverArtHolder &instance();

    void addCover(const QString &artist, const QString &albumName, QByteArray &coverArt);
    QByteArray getCover(const QString &artist, const QString &albumName) const;
    bool hasCover(const QString &artist, const QString &albumName) const;
private:
    QHash<CoverArtKey, QByteArray> coverArts;
};

#endif // COVERARTHOLDER_H
