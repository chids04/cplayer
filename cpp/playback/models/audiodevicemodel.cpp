#include "audiodevicemodel.h"

AudioDeviceModel::AudioDeviceModel(QObject *parent)
    : QAbstractListModel(parent) {
    // Initialize the model with the current audio devices
    m_mediaDevice = new QMediaDevices;

    updateDevices();

    QAudioDevice defaultDevice = QMediaDevices::defaultAudioOutput();
    for (int i = 0; i < m_audioDevices.size(); ++i) {
        if (m_audioDevices[i] == defaultDevice) {
            m_selectedIndex = i;  // Set default device as selected
            emit dataChanged(createIndex(m_selectedIndex, 0), createIndex(m_selectedIndex, 0), {Qt::DisplayRole, Qt::UserRole + 2});
            break;
        }
    }

    // Connect to QMediaDevices signal to update devices dynamically
    connect(m_mediaDevice, &QMediaDevices::audioOutputsChanged,
            this, &AudioDeviceModel::updateDevices);
}

int AudioDeviceModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_audioDevices.size();
}

QVariant AudioDeviceModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_audioDevices.size())
        return QVariant();

    const QAudioDevice &device = m_audioDevices.at(index.row());
    switch (role) {
    case DeviceNameRole:
        return device.description();
    case IsSelectedRole:
        return index.row() == m_selectedIndex;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> AudioDeviceModel::roleNames() const {
    return {
        {DeviceNameRole, "deviceName"},
        {IsSelectedRole, "isSelected"}
    };
}

void AudioDeviceModel::updateDevices() {
    beginResetModel();
    m_audioDevices = QMediaDevices::audioOutputs();
    endResetModel();
}

void AudioDeviceModel::selectDevice(int index)
{

    if (index < 0 || index >= m_audioDevices.size()) {
        qWarning() << "Invalid audio device index:" << index;
        return;
    }

    // Update the selected index
    if (m_selectedIndex != index) {
        int previousIndex = m_selectedIndex;
        m_selectedIndex = index;

        // Notify the view of the change
        emit dataChanged(createIndex(previousIndex, 0), createIndex(previousIndex, 0), {Qt::DisplayRole, AudioDeviceModel::IsSelectedRole});
        emit dataChanged(createIndex(m_selectedIndex, 0), createIndex(m_selectedIndex, 0), {Qt::DisplayRole, AudioDeviceModel::IsSelectedRole});
    }

    // Get the selected device
    const QAudioDevice &device = m_audioDevices.at(index);
    emit audioDeviceChanged(device);

    // Apply the selected device to the media player output
}
