#include "soundcloud.h"

#include <QtQml>
#include <QProcess>
#include <QAbstractListModel>

class SCPlaylist : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:

    enum SoundcloudRoles {
        TitleRole = Qt::UserRole + 1,
        ArtistRole,
        TypeRole,
        UrlRole,
        ArtworkUrlRole,
        DurationRole,
        DownloadableRole,
        TrackCountRole,
        PlaylistSongsRole,
    };
    explicit SCPlaylist(QObject *parent = nullptr);

    // Required QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Custom methods
    const SoundcloudItem& getItem(int index) const;


public slots:
    void setSongs(std::vector<SoundcloudItem> results);

private:
    std::vector<SoundcloudItem> m_results;
    QString formatDuration(int64_t milliseconds) const;


};
