#include "song.h"

Song::Song(const QString &filePath, const QString &title, const QString &artist, const QString &album, const QString &genre, const QStringList &featuringArtists, const QStringList &albumArtists, int year, int length, int trackNum)
    : filePath(filePath), title(title), artist(artist), album(album), genre(genre), featuringArtists(featuringArtists), albumArtists(albumArtists), year(year), length(length), trackNum(trackNum)  {}
