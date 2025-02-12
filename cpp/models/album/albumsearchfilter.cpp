#include "albumsearchfilter.h"

#include <rapidfuzz/fuzz.hpp>
#include <QRegularExpression>
#include <algorithm>

AlbumSearchFilter::AlbumSearchFilter(AlbumListModel *albumListModel, QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(albumListModel);
}

QString AlbumSearchFilter::filterString() const
{
    return m_filterString;
}

void AlbumSearchFilter::setFilterString(const QString &newFilterString)
{
    // Normalize the filter string: convert to lowercase and remove diacritical marks.
    QString normalizedFilter = normalizeString(newFilterString.toLower());
    if (m_filterString == normalizedFilter)
        return;
    m_filterString = normalizedFilter;
    invalidate();
    emit filterStringChanged();
}

QString AlbumSearchFilter::normalizeString(const QString &string) const
{
    // Normalize to compatibility decomposed form and remove nonspacing marks (accents)
    static QRegularExpression re(QStringLiteral("\\p{Mn}"));
    QString normalized = string.normalized(QString::NormalizationForm_KD);
    normalized.remove(re);
    return normalized;
}

double AlbumSearchFilter::computeMatchScore(const QStringList &tokens,
                                              const QString &albumName,
                                              const QStringList &albumArtists) const
{
    double scoreSum = 0.0;
    for (const QString &token : tokens) {
        // Fuzzy score for album name
        double albumNameScore = rapidfuzz::fuzz::partial_ratio(albumName.toStdString(), token.toStdString());

        // Compute the best fuzzy score among all album artists.
        double maxArtistScore = 0.0;
        for (const QString &artist : albumArtists) {
            double artistScore = rapidfuzz::fuzz::partial_ratio(artist.toStdString(), token.toStdString());
            maxArtistScore = std::max(maxArtistScore, artistScore);
        }
        // Weight the artist score more (e.g., 1.5×)
        double weightedArtistScore = maxArtistScore * 1.5;

        // For this token, take the higher score (album name vs. weighted artist)
        double tokenScore = std::max(albumNameScore, weightedArtistScore);
        scoreSum += tokenScore;
    }
    return scoreSum / tokens.size();
}

bool AlbumSearchFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_filterString.isEmpty())
        return true;

    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    // Get and normalize album name.
    QString albumName = sourceModel()->data(index, AlbumListModel::AlbumNameRole).toString().toLower();
    albumName = normalizeString(albumName);

    // Get and normalize album artists.
    QStringList albumArtists = sourceModel()->data(index, AlbumListModel::AlbumArtistRole).toStringList();
    for (int i = 0; i < albumArtists.size(); ++i) {
        albumArtists[i] = normalizeString(albumArtists[i].toLower());
    }

    // Tokenize the filter string (split by whitespace)
    QStringList tokens = m_filterString.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (tokens.isEmpty())
        return true;

    // Compute the overall match score.
    double score = computeMatchScore(tokens, albumName, albumArtists);

    // Accept the row if the score exceeds the threshold (adjust as needed)
    const double threshold = 40.0;
    return score > threshold;
}

bool AlbumSearchFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    // Retrieve and normalize album name and artists for the left item.
    QString leftAlbumName = sourceModel()->data(left, AlbumListModel::AlbumNameRole).toString().toLower();
    leftAlbumName = normalizeString(leftAlbumName);
    QStringList leftAlbumArtists = sourceModel()->data(left, AlbumListModel::AlbumArtistRole).toStringList();
    for (int i = 0; i < leftAlbumArtists.size(); ++i) {
        leftAlbumArtists[i] = normalizeString(leftAlbumArtists[i].toLower());
    }

    // Retrieve and normalize album name and artists for the right item.
    QString rightAlbumName = sourceModel()->data(right, AlbumListModel::AlbumNameRole).toString().toLower();
    rightAlbumName = normalizeString(rightAlbumName);
    QStringList rightAlbumArtists = sourceModel()->data(right, AlbumListModel::AlbumArtistRole).toStringList();
    for (int i = 0; i < rightAlbumArtists.size(); ++i) {
        rightAlbumArtists[i] = normalizeString(rightAlbumArtists[i].toLower());
    }

    // Tokenize the filter string.
    QStringList tokens = m_filterString.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (tokens.isEmpty())
        return QString::localeAwareCompare(leftAlbumName, rightAlbumName) < 0;

    // Compute match scores for both rows.
    double leftScore = computeMatchScore(tokens, leftAlbumName, leftAlbumArtists);
    double rightScore = computeMatchScore(tokens, rightAlbumName, rightAlbumArtists);

    // Higher scores indicate a better match so that better-matching rows appear first.
    return leftScore > rightScore;
}
