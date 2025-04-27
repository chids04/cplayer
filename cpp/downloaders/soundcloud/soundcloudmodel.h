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
        TrackCountRole,
        PlaylistSongsRole,
    };
    explicit SoundcloudModel(QObject *parent = nullptr);

    // Required QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Custom methods
    void setResults(const std::vector<SoundcloudItem>& results);
    const SoundcloudItem& getItem(int index) const;

signals:
    void searchStart();
    void searchEnd();
    void showMsg(const QString &msg);
    void downloadFailed();
    void scanForMusic(const QUrl &folderPath);

public slots:
    void newSearch(const QString &query);
    void download(int index);
    void handleSearchResults(const std::vector<SoundcloudItem>& results);

private slots:
    void onSongDlFinished(int exitCode, QProcess::ExitStatus exitStatus = QProcess::NormalExit);

private:
    std::vector<SoundcloudItem> m_results;
    QString formatDuration(int64_t milliseconds) const;

    QString downloader = "scdl";
    QProcess *dlProcess;
    QThread *searchThread;
    SoundcloudWrapper *wrapper;
    QString dlPath = R"(C:\Users\c\Music\scdl\)";
    int currentDlIdx = -1;

    

};

#endif // SOUNDCLOUDMODEL_H
