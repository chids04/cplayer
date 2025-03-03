#ifndef SOUNDCLOUDMODEL_H
#define SOUNDCLOUDMODEL_H

#include "soundcloud.h"

#include <QtQml>
#include <QProcess>
#include <QAbstractListModel>

class SoundcloudModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ANONYMOUS

public:

    enum SoundcloudRoles {
        TitleRole = Qt::UserRole + 1,
        ArtistRole,
        TypeRole,
        UrlRole,
        ArtworkUrlRole,
        DurationRole,
        DownloadableRole,
        TrackCountRole
    };
    explicit SoundcloudModel(QObject *parent = nullptr);

    // Required QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Custom methods
    void setResults(const std::vector<SoundcloudItem>& results);
    const SoundcloudItem& getItem(int index) const;

public slots:
    void newSearch(const QString &query);
    void download(int index);

private:
    std::vector<SoundcloudItem> m_results;
    QString formatDuration(int64_t milliseconds) const;

    SoundcloudWrapper *wrapper;
    QString downloader = "scdl";
    QProcess *dlProcess;

};

#endif // SOUNDCLOUDMODEL_H
