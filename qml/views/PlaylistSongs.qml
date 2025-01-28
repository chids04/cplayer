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
            Layout.preferredHeight: parent.height * 0.3
            Layout.fillWidth: true
            Layout.topMargin: 10

            clip: true



            RowLayout{
                anchors.fill: parent
                spacing: 10
                Image{
                    id: playlistCoverArt
                    Layout.preferredHeight: parent.height - 10
                    Layout.preferredWidth: parent.height - 10

                    source: GlobalSingleton.playlistManager.hasCover ? "image://playlistCovers" + "/" + GlobalSingleton.playlistManager.playlistID : "qrc:/resource/ui/assets/unknownCover.png"
                    sourceSize.width: parent.height - 10
                    sourceSize.height: parent.height - 10
                    cache: false

                }

                ColumnLayout{
                    Layout.fillHeight: true


                    Text{
                        id: loadedPlaylistName
                        color: "white"
                        text: GlobalSingleton.playlistManager.playlistName
                        font.bold: true
                        font.pointSize: 40


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

            CButton{
                id: playPlaylistBtn
                buttonText: "Play Playlist"

                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playPlaylist(GlobalSingleton.playlistManager.currentPlaylist)

                }

            }

            CButton{
                id: queuePlaylistBtn
                buttonText: "Queue Playlist"

                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playPlaylist(GlobalSingleton.playlistManager.currentPlaylist, true)
                }
            }
        }


        Rectangle{
            id: songList
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: playPlaylistBtn.height

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
