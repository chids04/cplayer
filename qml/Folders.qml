import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic

import com.c.MusicLibrary
import com.c.FolderView
import com.c.FolderModel

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


        ListView {
            id: folderListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            // anchors.fill: parent
            // anchors.topMargin: 10
            // anchors.rightMargin: 10
            // anchors.bottomMargin: 10

    //         ScrollBar.vertical: ScrollBar {
    //             id:songScollbar
    //             policy: ScrollBar.AlwaysOn

    //             width: 15

    //             contentItem: Rectangle {
    //                 implicitWidth: 15
    //                 radius: 3
    //                 color: "#606060"
    //             }

    //             background: Rectangle{
    //                 color: "transparent"
    //             }
    //         }

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

                    // MouseArea {
                    //     anchors.fill: parent
                    //     onDoubleClicked: {
                    //         MediaPlayerController.setSong(filePath, title, artist, album, features)
                    //     }
                    // }

    //                 RowLayout {

    //                     anchors{
    //                         fill: parent
    //                     }
    //                     spacing:0

    //                     Item {
    //                         Layout.preferredWidth: parent.width * 0.33
    //                         Layout.preferredHeight: parent.height

    //                         RowLayout{
    //                             anchors.fill: parent
    //                             spacing: 0

    //                             Image {
    //                                 width:60
    //                                 height:60
    //                                 source: "image://coverArt/" + album + "/" + artist
    //                                 sourceSize.width: 60
    //                                 sourceSize.height: 60
    //                                 Layout.rightMargin: 10
    //                                 Layout.leftMargin: 10
    //                             }

    //                             Text {
    //                                 //text: features[0] != "" ? artist + "feat. " + features.join(", ") : artist
    //                                 text: title
    //                                 font.bold: true
    //                                 color: "white"
    //                             }

    //                             Item{
    //                                 Layout.fillWidth: true
    //                             }


    //                         }


    //                     }

    //                     Item{
    //                         Layout.preferredWidth: parent.width * 0.33
    //                         Layout.preferredHeight: parent.height

    //                         Text {
    //                             color: "white"
    //                             text: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
    //                             anchors.centerIn: parent
    //                         }
    //                     }



    //                     Item{
    //                         Layout.preferredWidth: parent.width * 0.33
    //                         Layout.preferredHeight: parent.height

    //                         Text {
    //                             text: album
    //                             color: "white"
    //                             anchors.centerIn: parent
    //                         }
    //                     }


    //                 }


                }
            }

            model: FolderModel// This is the model exposed from C++
            delegate: folderDelegate

        }
    }
}
