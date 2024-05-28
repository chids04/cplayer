import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic

import "./qml"
import com.c.MediaController
import com.c.MusicLibrary

Window {
    width: 1280
    height: 720
    minimumWidth: 1024
    minimumHeight: 576
    visible: true
    title: qsTr("c")


    onVisibleChanged: {
        folderDialog.open()
    }

    FolderDialog{
        id: folderDialog
        title: "Select a directory to scan for music"

        onAccepted: {
            MusicLibrary.musicPath = folderDialog.folder
        }

    }

    Rectangle {
        anchors.fill: parent
        color: "#131314"

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            MainWindow{
            }

            MediaSlider{
            }


        }

    }

}

