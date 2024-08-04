#include "songfilterproxymodel.h"
#include "songlistmodel.h"
#include <QDebug>

SongFilterProxyModel::SongFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(&SongListModel::instance());
}

SongFilterProxyModel &SongFilterProxyModel::instance()
{
    static SongFilterProxyModel songFilterProxyModel;
    return songFilterProxyModel;
}

QString SongFilterProxyModel::filterString() const
{
    return m_filterString;
}

void SongFilterProxyModel::setFilterString(const QString &filterString)
{
    if (m_filterString != filterString) {
        m_filterString = normalizeString(filterString);
        //invalidateFilter();
        invalidate();
        emit filterStringChanged();
    }
}

bool SongFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_filterString.isEmpty()) {
        return true;
    }

    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString title = sourceModel()->data(index, SongListModel::TitleRole).toString();
    QString artist = sourceModel()->data(index, SongListModel::ArtistRole).toString();

    double titleScore = rapidfuzz::fuzz::partial_ratio(normalizeString(title).toStdString(), m_filterString.toStdString());
    double artistScore = rapidfuzz::fuzz::partial_ratio(normalizeString(artist).toStdString(), m_filterString.toStdString());


    return titleScore > 50;
}

bool SongFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QString leftTitle = sourceModel()->data(left, SongListModel::TitleRole).toString();
    QString rightTitle = sourceModel()->data(right, SongListModel::TitleRole).toString();
    QString normalizedLeftTitle = normalizeString(leftTitle);
    QString normalizedRightTitle = normalizeString(rightTitle);

    double leftScore = rapidfuzz::fuzz::partial_ratio(normalizedLeftTitle.toStdString(), m_filterString.toStdString());
    double rightScore = rapidfuzz::fuzz::partial_ratio(normalizedRightTitle.toStdString(), m_filterString.toStdString());


    return leftScore > rightScore;
}



QString SongFilterProxyModel::normalizeString(const QString &string) const
{
    static QRegularExpression re(QStringLiteral("\\p{Mn}"));
    QString normalized = string.normalized(QString::NormalizationForm_KD);
    normalized.remove(re);
    return normalized;
}
