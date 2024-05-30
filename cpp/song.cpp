#include "song.h"

Song::Song(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QStringList &featuringArtists, int length, int trackNum)
    : filePath(filePath), title(title), artist(artist), album(album), featuringArtists(featuringArtists), length(length), trackNum(trackNum)  {}
