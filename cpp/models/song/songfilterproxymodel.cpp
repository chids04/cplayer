#include "songfilterproxymodel.h"

#include <QDebug>
#include <QRegularExpression>
#include <rapidfuzz/fuzz.hpp>
#include "songlistmodel.h"

SongFilterProxyModel::SongFilterProxyModel(SongListModel *songListModel, QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(songListModel);
    setDynamicSortFilter(true);

    connect(songListModel, &SongListModel::refreshProxy, this, &SongFilterProxyModel::refreshFilter);
}

QString SongFilterProxyModel::filterString() const
{
    return m_filterString;
}

void SongFilterProxyModel::setFilterString(const QString &filterString)
{
    if (m_filterString != filterString) {
        m_filterString = normalizeString(filterString.toLower());
        //invalidateFilter();
        invalidate();
        emit filterStringChanged();
    }
}

bool SongFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    // if filter string is empty, show everything
    if (m_filterString.isEmpty())
        return true;

    QStringList tokens = m_filterString.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (tokens.isEmpty())
        return true;

    // Get data from the source model
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString title  = sourceModel()->data(index, SongListModel::TitleRole).toString().toLower();
    QString artist = sourceModel()->data(index, SongListModel::ArtistRole).toString().toLower();
    QString album  = sourceModel()->data(index, SongListModel::AlbumRole).toString().toLower();

    // Normalize the strings
    title  = normalizeString(title);
    artist = normalizeString(artist);
    album  = normalizeString(album);


    if(title.contains(m_filterString) || artist.contains(m_filterString) || album.contains(m_filterString)){
        return true;
    }

    double score = computeMatchScore(tokens, title, artist, album);

    const double threshold = 40.0;

    return score > threshold;
}

double SongFilterProxyModel::computeMatchScore(const QStringList &tokens,
    const QString &title,
    const QString &artist,
    const QString &album) const
{
    //match score capped to 1
    if(tokens.join(" ") == title){
        return 400;
    }

    double scoreSum = 0.0;
    for (const QString &token : tokens) {
        // Compute fuzzy scores (using rapidfuzz's partial_ratio)
        double titleScore  = rapidfuzz::fuzz::partial_ratio(title.toStdString(), token.toStdString())/100;
        double artistScore = rapidfuzz::fuzz::partial_ratio(artist.toStdString(), token.toStdString())/100;
        double albumScore  = rapidfuzz::fuzz::partial_ratio(album.toStdString(), token.toStdString())/100;

        // Weight the title more heavily (adjust the weight factors as desired)
        
        if(title == token){
            titleScore *= 1.5;
        }
        
        //double tokenScore = std::max({ weightedTitle, artistScore, albumScore });
        double tokenScore = titleScore + artistScore + albumScore;
        scoreSum += tokenScore;
    }
    // Return the average score across tokens
    return scoreSum / tokens.size() ;
}

bool SongFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    // Retrieve the fields for both left and right items.
    QString leftTitle  = sourceModel()->data(left, SongListModel::TitleRole).toString().toLower();
    QString leftArtist = sourceModel()->data(left, SongListModel::ArtistRole).toString().toLower();
    QString leftAlbum  = sourceModel()->data(left, SongListModel::AlbumRole).toString().toLower();
    QString rightTitle  = sourceModel()->data(right, SongListModel::TitleRole).toString().toLower();
    QString rightArtist = sourceModel()->data(right, SongListModel::ArtistRole).toString().toLower();
    QString rightAlbum  = sourceModel()->data(right, SongListModel::AlbumRole).toString().toLower();

    // Normalize them
    leftTitle  = normalizeString(leftTitle);
    leftArtist = normalizeString(leftArtist);
    leftAlbum  = normalizeString(leftAlbum);
    rightTitle  = normalizeString(rightTitle);
    rightArtist = normalizeString(rightArtist);
    rightAlbum  = normalizeString(rightAlbum);

    // Tokenize the current filter string
    QStringList tokens = m_filterString.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    // If no filter is active, fallback to a simple alphabetical order.
    if (tokens.isEmpty())
        return QString::localeAwareCompare(leftTitle, rightTitle) < 0;

    // Compute an overall matching score for each song.
    double leftScore = computeMatchScore(tokens, leftTitle, leftArtist, leftAlbum);
    double rightScore = computeMatchScore(tokens, rightTitle, rightArtist, rightAlbum);

    // We want higher scores to come first (i.e. a “better match” sorts before a lower one).
    // Thus, we say left is “less than” right if its score is higher.
    return leftScore > rightScore;
}

QString SongFilterProxyModel::normalizeString(const QString &string) const
{
    static QRegularExpression re(QStringLiteral("\\p{Mn}"));
    QString normalized = string.normalized(QString::NormalizationForm_KD);
    normalized.remove(re);
    return normalized;
}
