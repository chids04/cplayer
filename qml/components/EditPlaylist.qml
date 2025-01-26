pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic

import cplayer
import "../components"


Popup {
    id: popUp
    width: 600
    //height: 500
    modal: true
    focus: true
    dim: true
    anchors.centerIn: Overlay.overlay
    topPadding: 40

    property int playlistID
    property string playlistName
    property bool hasCover


    function openPopup(id, name, hasCover){
        popUp.playlistID = id
        popUp.playlistName = name
        popUp.hasCover = hasCover

        console.log(popUp.playlistID)
        console.log(popUp.hasCover)
        popUp.open()

    }

    enter: Transition {
        ParallelAnimation {
            id: popIn
            PropertyAnimation {
                target: popUp
                property: "scale"
                from: 0.9
                to: 1
                duration: 50
            }
            PropertyAnimation {
                target: popUp
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
                target: popUp
                property: "scale"
                from: 1
                to: 0.9
                duration: 50
            }
            PropertyAnimation {
                target: popUp
                property: "opacity"
                from: 1
                to: 0.9
                duration: 50
            }
        }
    }
    // Pop-up content
    background: Rectangle {
        id: popUpDelegate
        anchors.fill: parent
        color: "#191919"

        border.color: "#424345"
        border.width: 2
    }

    contentItem: ColumnLayout{
        //anchors.fill: parent
        id: content
        property bool hasCover;

        ErrorPopup{
            id: errorPopup
        }

        Image{
            id: playlistImg
            //source: "qrc:/resource/ui/assets/unknownCover.png"
            Layout.preferredHeight: 300
            Layout.preferredWidth: 300
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 10
            rotation: 0
            cache: false
            visible: false

        }


        RowLayout{
            Layout.alignment: Qt.AlignHCenter

            CButton {
                buttonText: "change image"
                Layout.alignment: Qt.AlignHCenter

                onButtonClicked: {
                    imageFileDialog.open()
                }
            }

            CButton {
                buttonText: "rotate image"
                Layout.alignment: Qt.AlignHCenter

                onButtonClicked: {
                    playlistImg.rotation = (playlistImg.rotation + 90) % 360
                }

            }

            CButton {
                buttonText: "remove image"
                Layout.alignment: Qt.AlignHCenter

                onButtonClicked: {
                    playlistImg.source = "qrc:/resource/ui/assets/unknownCover.png"
                }

            }


        }



        FileDialog{
            id: imageFileDialog
            title: "Select Playlist Cover Image"
            nameFilters: ["Image files (*.png *.jpg *.jpeg *.bmp)"]

            onAccepted: {
                playlistImg.source = file
                playlistImg.visible = true
                content.hasCover = true
            }
        }


        TextField {
            id: inputField
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 300
            text: popUp.playlistName
            placeholderText: "Enter Playlist Name"
            placeholderTextColor: "#6a6f76"
            color: "white"

            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10

            }

            TextMetrics{
                id: metrics
                elideWidth: inputField.width
            }

        }


        CButton{
            buttonText: "modify"
            Layout.alignment: Qt.AlignRight

            onButtonClicked: {
                if(inputField.text.trim() === ""){
                    errorPopup.openPopup("Playlist must have a name")
                }
                else{
                    //PlaylistView.addPlaylist(inputField.text)
                    if(content.hasCover || popUp.hasCover){
                        GlobalSingleton.playlistManager.modifyPlaylist(popUp.playlistID, inputField.text, playlistImg.rotation, playlistImg.source, true)
                        popUp.close()
                    }
                    else{
                        GlobalSingleton.playlistManager.modifyPlaylist(popUp.playlistID, inputField.text, playlistImg.rotation)
                        popUp.close()
                    }

                }
            }
        }
    }


}

