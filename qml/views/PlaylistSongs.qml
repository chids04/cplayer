pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import cplayer

import "../components"

Item {

    ColumnLayout{
        anchors.fill: parent

        Item{
            id: playlistInfo
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
                    id: playlistCoverArt
                    Layout.alignment: Qt.AlignHCenter
                    source: GlobalSingleton.playlistManager.hasCover ? "image://playlistCovers" + "/" + GlobalSingleton.playlistManager.playlistID : "qrc:/resource/ui/assets/unknownCover.png"
                    sourceSize.width: 200
                    sourceSize.height: 200
                    asynchronous: true
                    cache: false

                }

                Text{
                    id: loadedPlaylistName
                    color: "white"
                    text: GlobalSingleton.playlistManager.playlistName
                    Layout.alignment: Qt.AlignHCenter
                    font.bold: true
                    font.pointSize: 40
                } 
            }
        }
        RowLayout{

            CButton{
                id: playPlaylistBtn
                buttonText: "Play Playlist"
                buttonTextSize: 10
                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playPlaylist(GlobalSingleton.playlistManager.currentPlaylist)

                }
            }

            CButton{
                id: queuePlaylistBtn
                buttonText: "Queue Playlist"
                buttonTextSize: 10
                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playPlaylist(GlobalSingleton.playlistManager.currentPlaylist, true)
                }
            }
        }


        Rectangle{
            id: songList
            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "transparent"
            ListView {
                id: playlistSongsListView
                anchors.fill: parent
                anchors.topMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 10
                clip: true

                ScrollBar.vertical: ScrollBar {
                    id:playlistScrollBar
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

                //model: PlaylistView.playlistSongsModel
                model: GlobalSingleton.playlistManager.playlistSongs

                delegate: SongDelegate{
                    id: songDelegate


                    songDelegateHeight: 63
                    songDelegateWidth: playlistSongsListView.width - 23

                    onSongDelegateDoubleClicked: {
                        GlobalSingleton.playbackManager.nowPlaying.playNow(songObj)
                    }

                    onSongDelegateRightClicked: {
                        playlistSongsListView.interactive = false
                        contextMenu.currDelegate = playlistSongsListView.itemAtIndex(index)
                        contextMenu.openContextMenu(songObj)
                    }
                }

                SongContextMenu{
                    id: contextMenu
                    property SongDelegate currDelegate

                    onPopupClosed: {
                        if(currDelegate){
                            playlistSongsListView.interactive = true
                            currDelegate.overlay = "transparent"
                            currDelegate.isContextMenuOpen = false
                        }
                    }

                }

            }



        }
    }
}
