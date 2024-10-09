import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import cplayer

Popup {
    id: folderPopup
    modal: true
    focus: true
    padding: 20
    anchors.centerIn: Overlay.overlay
    dim: true

    property int index
    property string folderPath

    function openFolderPopup(folderIndex, path){
        index = folderIndex
        folderPath = path
        folderPopup.open()
    }

    enter: Transition {
                ParallelAnimation {
                    id: popIn
                    PropertyAnimation {
                        target: folderPopup
                        property: "scale"
                        from: 0.9
                        to: 1
                        duration: 50
                    }
                    PropertyAnimation {
                        target: folderPopup
                        property: "opacity"
                        from: 0.9
                        to: 1
                        duration: 50
                    }
                }
            }
            exit: Transition {
                ParallelAnimation {
                    id: popOut
                    PropertyAnimation {
                        target: folderPopup
                        property: "scale"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                    PropertyAnimation {
                        target: folderPopup
                        property: "opacity"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                }
            }

        background: Rectangle{
            anchors.fill: parent
            width: text2Width.width >= text1Width ? text2Width : text1Width
            color: "#202020"
            border.color: "#2f3137"
            border.width: 2
            radius: 20
        }

    contentItem: ColumnLayout {
            spacing: 0
            anchors.fill: parent
            Text {
                id: confirmText
                text: "are you sure you would like to delete folder:"
                font.pointSize: 20
                color: "white"
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                Layout.bottomMargin: 5

                TextMetrics{
                    id: text1Width
                    text: confirmText.text
                }
            }
            Text{
                id: folderPathText
                text: folderPath
                font.pointSize: 8
                font.bold: true
                color: "white"
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                TextMetrics{
                    id: text2Width
                    text: folderPathText.text
                }
            }

            CButton{
                id: deleteFolderBtn
                buttonText: "delete folder"
                buttonTextSize: 10
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                onButtonClicked: {
                    ViewController.folderView.removeFolder(index, folderPath)
                    folderPopup.close()
                }

            }

        }



}
