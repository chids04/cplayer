#include "utilitysingleton.h"

SettingsManager *UtilitySingleton::settingsManager() const
{
    return m_settingsManager;
}

void UtilitySingleton::setSettingsManager(SettingsManager *newSettingsManager)
{
    if (m_settingsManager == newSettingsManager)
        return;
    m_settingsManager = newSettingsManager;
    emit settingsManagerChanged();
}
