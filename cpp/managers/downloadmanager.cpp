#include "downloadmanager.h"
#include "soundcloudmodel.h"
#include <pybind11/pybind11.h>


DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{
    setScModel(new SoundcloudModel);

    connect(m_scModel, &SoundcloudModel::showMsg, this, &DownloadManager::onShowMsg);
    connect(m_scModel, &SoundcloudModel::scanForMusic, this, &DownloadManager::scanForMusic);
}

SoundcloudModel *DownloadManager::scModel() const
{
    return m_scModel;
}

void DownloadManager::setScModel(SoundcloudModel *newScModel)
{
    if (m_scModel == newScModel)
        return;
    m_scModel = newScModel;
    emit scModelChanged();
}

void DownloadManager::onShowMsg(const QString &msg) {
    emit showMsg(msg);
}
