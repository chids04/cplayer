pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import cplayer

import "../components"

Item {
    id: view
    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Item{
            id: albumInfo
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.preferredHeight: childrenRect.height

            clip: true

            ColumnLayout{
                spacing: 10
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                }

                Image{
                    id: albumCoverArt
                    Layout.alignment: Qt.AlignHCenter
                    source: "image://coverArt/" + GlobalSingleton.songManager.albumName + "/" + GlobalSingleton.songManager.albumArtists.join("++?")
                    sourceSize.width: 250
                    sourceSize.height: 250

                }

                Text{
                    id: loadedAlbumName
                    color: "white"
                    text: GlobalSingleton.songManager.albumName
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                    font.bold: true
                    font.pointSize: 32

                }

                Text{
                    id: loadedAlbumArtists
                    Layout.alignment: Qt.AlignHCenter
                    text: GlobalSingleton.songManager.albumArtists.join(", ")
                    color:"white"
                    font.pointSize: 20
                }

                Text{
                    id: loadedAlbumGenre
                    Layout.alignment: Qt.AlignHCenter
                    text: GlobalSingleton.songManager.albumGenre
                    color: "white"
                    font.pointSize: 10
                }

                Text{
                    id: loadedAlbumYear
                    Layout.alignment: Qt.AlignHCenter
                    text: GlobalSingleton.songManager.albumYear
                    color: "white"
                    font.pointSize: 10
                }

            }
        }

        RowLayout{
            id: albumControls

            CButton{
                id: playAlbumBtn
                buttonText: "Play Now"
                buttonTextSize: 10
                

                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playAlbum(GlobalSingleton.songManager.albumName, GlobalSingleton.songManager.albumArtists, false);
                }

            }

            CButton{
                id: queueAlbumBtn
                buttonText: "Add to Queue"
                buttonTextSize: 10

                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playAlbum(GlobalSingleton.songManager.albumName, GlobalSingleton.songManager.albumArtists, true);
                    let albumNameBold = "<b>" + GlobalSingleton.songManager.albumName + "</b>";
                    GlobalSingleton.viewController.showMsg(albumNameBold + " added to queue")
                }
            }


        }

        Rectangle{
            id: songList
            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "transparent"
            ListView {
                id: albumSongsListView
                anchors.fill: parent
                anchors.topMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 10
                clip: true

                ScrollBar.vertical: ScrollBar {
                    id:albumScrollBar
                    policy: ScrollBar.AlwaysOn

                    width: 15

                    contentItem: Rectangle {
                        implicitWidth: 15
                        radius: 3
                        color: "#606060"
                    }

                    background: Rectangle{
                        color: "transparent"
                    }
                }

                model: GlobalSingleton.songManager.albumSongsModel

                delegate: SongDelegate{
                    id: songDelegate


                    songDelegateHeight: 63
                    songDelegateWidth: albumSongsListView.width - 23

                    notForAlbum: false

                    onSongDelegateDoubleClicked: {
                        GlobalSingleton.playbackManager.nowPlaying.playNow(songObj)
                    }

                    onSongDelegateRightClicked: {
                        albumSongsListView.interactive = false
                        contextMenu.currDelegate = albumSongsListView.itemAtIndex(index)
                        contextMenu.openContextMenu(songObj)
                    }

                }
                SongContextMenu{
                    id: contextMenu
                    property SongDelegate currDelegate

                    onPopupClosed: {
                        if(currDelegate){
                            albumSongsListView.interactive = true
                            currDelegate.overlay = "transparent"
                            currDelegate.isContextMenuOpen = false
                        }
                    }

                }

            }



        }
    }
}

