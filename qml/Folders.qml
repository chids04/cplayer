import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic

import com.c.MusicLibrary
import com.c.FolderView

import "./components"


Item {
    id: folderView

    FolderDialog{
        id: folderDialog
        title: "Select a directory to scan for music"

        onAccepted: {
            FolderView.startFolderScanningThread(folderDialog.folder)
        }

    }

    ColumnLayout{
        anchors.fill: parent
        RowLayout{

            Layout.fillWidth: true
            spacing: 20

            Text{
                text: "Folders"
                font.bold: true
                font.pointSize: 100
                color: "white"
                Layout.preferredWidth: width
            }

            CButton{
                id: addFoldlerbtn
                buttonText: "Add folder to scan for music"
                buttonTextSize: 24
                Layout.preferredWidth: width

                onButtonClicked: {
                    folderDialog.open()
                }
            }

        }



        Item{
            Layout.fillHeight: true
        }
    }
}
