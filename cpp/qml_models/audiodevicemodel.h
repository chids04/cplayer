#ifndef AUDIODEVICEMODEL_H
#define AUDIODEVICEMODEL_H

#include <QAbstractListModel>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QtQml/qqmlregistration.h>


class AudioDeviceModel : public QAbstractListModel {
    Q_OBJECT
    QML_UNCREATABLE("Audio device model cannot be intantiated")
    QML_ELEMENT

public:
    explicit AudioDeviceModel(QObject *parent = nullptr);

    enum Roles {
        DeviceNameRole = Qt::UserRole + 1, // Custom role for device name
        IsSelectedRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void audioDeviceChanged(const QAudioDevice &device);

public slots:
    void updateDevices();
    void selectDevice(int index);

private:
    QList<QAudioDevice> m_audioDevices;
    QMediaDevices *m_mediaDevice;
    int m_selectedIndex = -1;
};

#endif // AUDIODEVICEMODEL_H

