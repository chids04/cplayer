#include "downloadmanager.h"
#include <pybind11/pybind11.h>


DownloadManager::DownloadManager(QObject *parent) : QObject(parent)
{
    setScModel(new SoundcloudModel);
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
