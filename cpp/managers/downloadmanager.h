#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include "soundcloudmodel.h"

#include <QObject>
#include <QtQml/qqmlregistration.h>

class DownloadManager : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS
    Q_PROPERTY(SoundcloudModel *scModel READ scModel WRITE setScModel NOTIFY scModelChanged)
public:
    explicit DownloadManager(QObject* parent=nullptr);

    SoundcloudModel *scModel() const;
    void setScModel(SoundcloudModel *newScModel);

signals:
    void scModelChanged();
private:
    SoundcloudModel *m_scModel = nullptr;
};

#endif // DOWNLOADMANAGER_H
