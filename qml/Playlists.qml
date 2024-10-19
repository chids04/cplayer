import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Dialogs
import QtQuick.Controls.Basic

import cplayer

import "./components"
import "../.."


Item {
    id: playlistsView

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

                    Image{
                        source: "qrc:/resource/ui/assets/unknownCover.png"
                        Layout.preferredHeight: 300
                        Layout.preferredWidth: 300
                        Layout.alignment: Qt.AlignHCenter
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
                                mainErrorPopup.openPopup("Playlist must have a name")
                            }
                            else{
                                //PlaylistView.addPlaylist(inputField.text)
                                MusicHandler.playlistManager.addPlaylist(inputField.text)
                                popUp.close()
                            }
                        }
                    }
                }


                // Blurring the main window when the pop-up is open
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

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true

                            onEntered: {
                                playlistCard.color = "#0b0b0b"

                            }
                            onExited: {
                                playlistCard.color = "transparent"
                            }

                            onDoubleClicked:{
                                // AlbumFilterModel.setAlbumName(albumName)
                                // AlbumSongsView.setAlbum(albumArtists, albumName, albumGenre, albumYear, albumSongCount)
                                // ViewController.selectAlbum()
                                //PlaylistView.loadPlaylistSongs(playlistID)
                                MusicHandler.playlistManager.loadPlaylistSongs(playlistID)
                                ModelHandler.setPlaylistSongsList(MusicHandler.playlistManager.playlistSongsModel)
                                ViewController.selectPlaylist()
                            }

                        }

                        ColumnLayout{
                            spacing: 0
                            anchors.fill: parent
                            anchors.bottomMargin: 5

                            Image {
                                source: playlistHasCover ? "img://coverArt" + playlistName + "/" + playlistID : "qrc:/resource/ui/assets/unknownCover.png"
                                sourceSize.width: playlistCard.width - 100
                                sourceSize.height: playlistCard.width - 100
                                Layout.alignment: Qt.AlignHCenter

                            }

                            Text {
                                text: playlistName
                                font.bold: true
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                color: "white"
                                Layout.alignment: Qt.AlignHCenter
                                Layout.bottomMargin: 7
                            }

                        }
                    }
                }

                model: ModelHandler.playlistList
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
