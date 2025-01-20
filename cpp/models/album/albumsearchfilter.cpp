#include "albumsearchfilter.h"

#include <rapidfuzz/fuzz.hpp>

AlbumSearchFilter::AlbumSearchFilter(AlbumListModel *albumListModel, QObject *parent) : QSortFilterProxyModel(parent)
{
    setSourceModel(albumListModel);
}


QString AlbumSearchFilter::filterString() const
{
    return m_filterString;
}


void AlbumSearchFilter::setFilterString(const QString &newFilterString)
{
    if (m_filterString == newFilterString)
        return;
    m_filterString = normalizeString(newFilterString);
    invalidate();
    emit filterStringChanged();
}
//album up2me by yeat
//album name up2me
//artist yeat
//info to send will b up2me yeat <- as string to compare against

bool AlbumSearchFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_filterString.isEmpty()) {
        return true;
    }

    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString title = sourceModel()->data(index, AlbumListModel::AlbumNameRole).toString();
    QStringList artists = sourceModel()->data(index, AlbumListModel::AlbumArtistRole).toStringList();

    QStringList normalizedArtists;
    normalizedArtists.append(normalizeString(title));

    for(const QString &artist : artists){
        normalizedArtists.append(normalizeString(artist));
    }

    double score = rapidfuzz::fuzz::partial_ratio(normalizedArtists.join(" ").toStdString(),m_filterString.toStdString());

    return score > 30;
}

bool AlbumSearchFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    //construct ALBUMNAME + ALBUM ARTISTS type filter string

    QString leftTitle = sourceModel()->data(left, AlbumListModel::AlbumNameRole).toString();
    QString rightTitle = sourceModel()->data(right, AlbumListModel::AlbumNameRole).toString();


    QStringList leftArtists = sourceModel()->data(left, AlbumListModel::AlbumArtistRole).toStringList();
    QStringList rightArtists = sourceModel()->data(right, AlbumListModel::AlbumArtistRole).toStringList();

    QString normalizedLeftTitle = normalizeString(leftTitle);
    QString normalizedRightTitle = normalizeString(rightTitle);

    QStringList normalizedLeftArtists;
    normalizedLeftArtists.append(normalizedLeftTitle);
    QStringList normalizedRightArtists;
    normalizedRightArtists.append(normalizedRightTitle);

    for(const QString &artist : leftArtists){
        normalizedLeftArtists.append(normalizeString(artist));
    }

    for(const QString &artist : rightArtists){
        normalizedRightArtists.append(normalizeString(artist));
    }

    double leftScore = rapidfuzz::fuzz::partial_ratio(normalizedLeftArtists.join(" ").toStdString(), m_filterString.toStdString());
    double rightScore = rapidfuzz::fuzz::partial_ratio(normalizedRightArtists.join(" ").toStdString(), m_filterString.toStdString());

    return leftScore > rightScore;
}

QString AlbumSearchFilter::normalizeString(const QString &string) const
{
    static QRegularExpression re(QStringLiteral("\\p{Mn}"));
    QString normalized = string.normalized(QString::NormalizationForm_KD);
    normalized.remove(re);
    return normalized;
}

