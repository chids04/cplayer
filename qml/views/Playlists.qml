pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic

import cplayer

import "../components"


Item {
    id: playlistsView

    ErrorPopup{
        id: errorPopup
    }

    ColumnLayout{
        anchors.fill: parent

        RowLayout{
            Layout.fillWidth: true
            spacing: 20

            Text{
                text: "playlists"
                font.bold: true
                font.pointSize: 100
                color: "white"
                Layout.preferredWidth: width
            }

            CButton{
                id: addPlaylistButton
                buttonText: "Add Playlist"
                buttonTextSize: 24
                Layout.preferredWidth: width

                onButtonClicked: {
                    popUp.open()
                }

            }

            Popup {
                id: popUp
                width: 600
                //height: 500
                modal: true
                focus: true
                dim: true
                anchors.centerIn: Overlay.overlay
                topPadding: 40

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
                    color: "#202020"

                    border.color: "#2f3137"
                    border.width: 2
                }

                contentItem: ColumnLayout{
                    //anchors.fill: parent
                    id: content
                    property bool hasCover;

                    Image{
                        id: playlistImg
                        source: "qrc:/resource/ui/assets/unknownCover.png"
                        Layout.preferredHeight: 300
                        Layout.preferredWidth: 300
                        Layout.alignment: Qt.AlignHCenter
                        Layout.bottomMargin: 10
                        rotation: 0
                    }


                    RowLayout{
                        Layout.alignment: Qt.AlignHCenter

                        CButton {
                            buttonText: "add image"
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


                    }



                    FileDialog{
                        id: imageFileDialog
                        title: "Select Playlist Cover Image"
                        nameFilters: ["Image files (*.png *.jpg *.jpeg *.bmp)"]

                        onAccepted: {
                            playlistImg.source = file
                            content.hasCover = true
                        }
                    }


                    TextField {
                        id: inputField
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredWidth: 300
                        placeholderText: "Enter Playlist Name"
                        placeholderTextColor: "#6a6f76"
                        color: "white"

                        background: Rectangle{
                            color: "#2f3137"
                            radius: 10

                        }

                        TextMetrics{
                            id: metrics
                            elideWidth: inputField.width
                        }

                    }


                    CButton{
                        buttonText: "Add Playlist"
                        Layout.alignment: Qt.AlignRight

                        onButtonClicked: {
                            if(inputField.text.trim() === ""){
                                errorPopup.openPopup("Playlist must have a name")
                            }
                            else{
                                //PlaylistView.addPlaylist(inputField.text)
                                if(content.hasCover){
                                    GlobalSingleton.playlistManager.addPlaylist(inputField.text, playlistImg.rotation, playlistImg.source, true)
                                    popUp.close()
                                }
                                else{
                                    GlobalSingleton.playlistManager.addPlaylist(inputField.text, playlistImg.rotation)
                                    popUp.close()
                                }

                            }
                        }
                    }
                }


            }

        }

        Item {
            id: playlistWindow
            Layout.fillHeight: true
            Layout.fillWidth: true

            property int minColumns: 5
            property int maxColumns: 5
            property real itemWidth: Math.max(gridView.width / maxColumns, gridView.width / minColumns)

            Timer {
                id: resizeTimer
                interval: 200
                repeat: false
                onTriggered: {
                    playlistWindow.itemWidth = Math.max(gridView.width / playlistWindow.maxColumns, gridView.width / playlistWindow.minColumns)
                    gridView.cellWidth = playlistWindow.itemWidth
                    gridView.cellHeight = playlistWindow.itemWidth

                }
            }



            GridView {
                id: gridView
                anchors.fill: parent
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                cellWidth: playlistWindow.itemWidth
                cellHeight: playlistWindow.itemWidth
                clip: true


                Component{
                    id: playlistDelegate

                    Rectangle{
                        id: playlistCard
                        width: gridView.cellWidth
                        height: gridView.cellHeight
                        color: "transparent"
                        radius: 10

                        required property int playlistID
                        required property string playlistName
                        required property bool playlistHasCover

                        property bool isHovered: false
                        property bool isContextMenuOpened: false

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.LeftButton | Qt.RightButton

                            onEntered: {
                                playlistCard.color = "#0b0b0b"
                                playlistCard.isHovered = true

                            }
                            onExited: {
                                if(!playlistCard.isContextMenuOpened){
                                    playlistCard.isHovered = false
                                    playlistCard.color = "transparent"
                                }


                            }

                            onDoubleClicked:{
                                // AlbumFilterModel.setAlbumName(albumName)
                                // AlbumSongsView.setAlbum(albumArtists, albumName, albumGenre, albumYear, albumSongCount)
                                // ViewController.selectAlbum()
                                //PlaylistView.loadPlaylistSongs(playlistID)
                                GlobalSingleton.playlistManager.loadPlaylistSongs(playlistCard.playlistID)
                                GlobalSingleton.viewController.selectPlaylist()
                            }

                            onClicked: mouse => {
                                if(mouse.button === Qt.RightButton){
                                    console.log(playlistCard.playlistID, playlistCard.playlistHasCover)
                                    playlistCard.isContextMenuOpened = true
                                    playlistContextMenu.openContextMenu(playlistCard.playlistID, playlistCard.playlistName, playlistCard.playlistHasCover)
                                }
                            }


                        }

                        ColumnLayout{
                            spacing: 0
                            anchors.fill: parent
                            anchors.bottomMargin: 5

                            Image {
                                source: playlistCard.playlistHasCover ? "image://playlistCovers" + "/" + playlistCard.playlistID : "qrc:/resource/ui/assets/unknownCover.png"
                                sourceSize.width: playlistCard.width - 100
                                sourceSize.height: playlistCard.width - 100
                                Layout.alignment: Qt.AlignHCenter
                                cache: false

                            }

                            Text {
                                text: playlistCard.playlistName
                                font.bold: true
                                //wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                color: "white"
                                Layout.alignment: Qt.AlignHCenter
                                Layout.bottomMargin: 7
                            }


                            PlaylistContextMenu{
                                id: playlistContextMenu
                                onClosed: {
                                    playlistCard.isContextMenuOpened = false
                                    playlistCard.color = "transparent"
                                }
                            }
                        }
                    }
                }

                model: GlobalSingleton.playlistManager.playlistModel
                delegate: playlistDelegate

                onWidthChanged: {
                    resizeTimer.restart()

                }
                onHeightChanged: {
                    resizeTimer.restart()
                }

            }
        }

    }


}
