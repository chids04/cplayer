#ifndef UTILITYSINGLETON_H
#define UTILITYSINGLETON_H

#include <QtQml>
#include <QObject>

#include "settingsmanager.h"

class UtilitySingleton : public QObject{

    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

    Q_PROPERTY(SettingsManager* settingsManager READ settingsManager WRITE setSettingsManager NOTIFY settingsManagerChanged)

public:
    SettingsManager *settingsManager() const;
    void setSettingsManager(SettingsManager *newSettingsManager);

signals:
    void settingsManagerChanged();

private:
    SettingsManager *m_settingsManager = nullptr;
};

#endif // UTILITYSINGLETON_H
