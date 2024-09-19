import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls

import cplayer
import "./components"

Item {

    FolderDialog{
        id: folderDialogs
        title: "Select a directory to scan for music"

        onAccepted: {
            print(folderDialogs.folder)
            ViewController.folderView.startFolderScanningThread(folderDialogs.folder)
        }
    }

    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Text{
            text: "settings"
            font.bold: true
            font.pointSize: 100
            color: "white"
            Layout.fillWidth: true
            Layout.bottomMargin: 20
        }

        Rectangle {
            height: 1
            color: "#2e2f30"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            Layout.bottomMargin: 20
            Layout.rightMargin: 10
        }


        Text{
            text: "folders"
            font.bold: true
            font.pointSize: 30
            color: "white"
        }

        RowLayout{

            Text{
                text: "folders being scanned for music"
                font.pointSize: 12
                color: "darkgrey"
            }

            CButton{
                buttonText: "add folder"
                buttonTextSize: 10
                onButtonClicked: folderDialogs.open()
            }
        }

        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.rightMargin: 10
            border.color: "#2e2f30"
            border.width: 2
            color: "transparent"

            ListView{
                id: folderListView
                anchors.fill: parent
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                spacing: 5
                clip: true

                delegate: FolderDelegate{
                    folderDelegateName: folderName
                    folderDelegatePath: folderPath
                    delegateWidth: folderListView.width
                }

                model: ModelHandler.folderList
            }

        }




        Item{
            Layout.fillHeight: true
        }
    }
}
