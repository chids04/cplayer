import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic

import cplayer
import "../components"

Item {
    id: folderView

    FolderDialog{
        id: folderDialog
        title: "Select a directory to scan for music"

        onAccepted: {
            ViewController.folderView.startFolderScanningThread(folderDialog.folder)
            //FolderView.startFolderScanningThread(folderDialog.folder)
        }

    }


    ColumnLayout{
        anchors.fill: parent
        RowLayout{

            Layout.fillWidth: true
            spacing: 20

            Text{
                text: "folders"
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


        ListView {
            id: folderListView
            Layout.fillHeight: true
            Layout.fillWidth: true

            Component {
                id:folderDelegate

                Rectangle {
                    id: folderRect
                    width: folderListView.width-23
                    height: 90
                    radius: 10
                    color: index % 2 == 0 ? "#1e1f20" : "#131314"

                    RowLayout{
                        anchors.fill: parent

                        Item{
                            Layout.preferredWidth: parent.width*0.1
                            Layout.fillHeight: true

                            Image {
                                anchors.centerIn: parent
                                source: "qrc:/resource/ui/assets/folderIcon.png"
                                width: 40
                                height: 40

                            }
                        }

                        Item{
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            ColumnLayout{
                                anchors.fill: parent

                                Text{
                                    text: folderName
                                    font.bold: true
                                    font.pointSize: 16
                                    color: "white"
                                }

                                Text{
                                    text: folderPath
                                    color: "white"
                                }

                                Text{
                                    text: "Number of Songs: " + folderSongCount
                                    color: "white"

                                }
                            }
                        }


                    }

                }
            }

            //model: FolderModel// This is the model exposed from C++
            model: ModelHandler.folderList
            delegate: folderDelegate

        }
    }
}
