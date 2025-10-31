#ifndef COVERIMGPROVIDER_H
#define COVERIMGPROVIDER_H

#include <QUrl>
#include <QString>
#include <QSettings>
#include <QQuickImageProvider>

struct CoverArtKey{
    QStringList artists;
    QString albumName;

    bool operator==(const CoverArtKey &other) const {
        return artists == other.artists && albumName == other.albumName;
    }

    QString toString() const {
        return artists.join(',') + "|" + albumName;
    }

    static CoverArtKey fromString(const QString &str) {
        QStringList parts = str.split("|");
        CoverArtKey key;
        key.artists = parts[0].split(",");  // Split artists by commas
        key.albumName = parts[1];
        return key;
    }
};

//simple hashing function
inline uint qHash(const CoverArtKey &key, uint seed = 0){
    uint hash = seed;

    for(const QString &artist : key.artists){
        hash ^= qHash(artist, seed);
    }

    return hash ^ qHash(key.albumName);
}


class CoverImgProvider : public QQuickImageProvider
{

public:
    CoverImgProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);


    void addCover(const QStringList &artists, const QString &albumName, QByteArray &coverArt);
    QByteArray getCover(const QStringList &artists, const QString &albumName) const;
    bool hasCover(const QStringList &artists, const QString &albumName) const;
    bool coverExists(const QStringList &artists, const QString &albumName) const;
    void loadFromSettings();
    void saveCoverArts();

private:
    QHash<CoverArtKey, QByteArray> coverArts;
    QSet<CoverArtKey> covers;


};

#endif // COVERIMGPROVIDER_H
