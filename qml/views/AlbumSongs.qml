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

            RowLayout{
                spacing: 10
                anchors.left: parent.left
                anchors.right: parent.right

                Item{
                    Layout.preferredWidth: parent.width * 0.25
                    Layout.preferredHeight: childrenRect.height

                    Image{
                        id: albumCoverArt

                        anchors {
                            left: parent.left
                            verticalCenter: parent.verticalCenter
                        }

                        source: "image://coverArt/" + GlobalSingleton.songManager.albumName + "/" + GlobalSingleton.songManager.albumArtists.join("++?")
                        sourceSize.width: 150
                        sourceSize.height: 150

                    }
                }

                Item{
                    Layout.preferredWidth: parent.width * 0.5
                    Layout.preferredHeight: childrenRect.height

                    ColumnLayout{
                        anchors{
                            left: parent.left
                            right: parent.right
                            top: parent.top
                        }

                        Text{
                            id: loadedAlbumName
                            elide: Text.ElideRight
                            Layout.alignment: Qt.AlignCenter
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter

                            text: GlobalSingleton.songManager.albumName
                            color: "white"
                            font.bold: true
                            font.pointSize: 32
                        }

                        Text{
                            id: loadedAlbumArtists
                            Layout.alignment: Qt.AlignCenter
                            text: GlobalSingleton.songManager.albumArtists.join(", ")
                            color:"white"
                            font.pointSize: 20
                        }

                    }
                    
                }

                

                Item{
                    Layout.preferredHeight: childrenRect.height
                    Layout.preferredWidth: parent.width * 0.25


                    ColumnLayout{
                        anchors{
                            top: parent.right
                            right: parent.right
                            rightMargin: 50
                        }

                        Text{
                            id: loadedAlbumGenre
                            text: GlobalSingleton.songManager.albumGenre
                            color: "white"
                            font.pointSize: 18
                        }

                        Text{
                            id: loadedAlbumYear
                            text: GlobalSingleton.songManager.albumYear
                            color: "white"
                            font.pointSize: 18
                            Layout.alignment: Qt.AlignHCenter
                        }
                } 
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

