pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import cplayer

import "../components"

Item {

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Item{
            id: albumInfo
            Layout.preferredHeight: parent.height * 0.3
            Layout.fillWidth: true
            Layout.topMargin: 10

            clip: true



            RowLayout{
                anchors.fill: parent
                spacing: 10
                Image{
                    id: albumCoverArt

                    source: "image://coverArt/" + GlobalSingleton.songManager.albumName + "/" + GlobalSingleton.songManager.albumArtists[0]
                    sourceSize.width: 170
                    sourceSize.height: 170

                }

                ColumnLayout{
                    Layout.fillHeight: true


                    Text{
                        id: loadedAlbumName
                        color: "white"
                        text: GlobalSingleton.songManager.albumName
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                        font.bold: true
                        font.pointSize: 40

                    }

                    Text{
                        id: loadedAlbumArtists
                        text: GlobalSingleton.songManager.albumArtists.join(", ")
                        color:"white"
                        font.pointSize: 20
                    }

                    Text{
                        id: loadedAlbumGenre
                        text: GlobalSingleton.songManager.albumGenre
                        color: "white"
                        font.pointSize: 10
                    }

                    Text{
                        id: loadedAlbumYear
                        text: GlobalSingleton.songManager.albumYear
                        color: "white"
                        font.pointSize: 10
                    }
                }

                Rectangle{ //filler item
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                }
            }
        }

        RowLayout{
            id: albumControls

            CButton{
                id: playAlbumBtn
                buttonText: "Play Now"

                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playAlbum(GlobalSingleton.songManager.albumName, GlobalSingleton.songManager.albumArtists, false);
                }

            }

            CButton{
                id: queueAlbumBtn
                buttonText: "Add to Queue"

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

