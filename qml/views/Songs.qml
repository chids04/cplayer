pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import cplayer


Item {
    id:songsWindow

    ColumnLayout{
        anchors.fill: parent

        Text{
            text: "songs"
            font.bold: true
            font.pointSize: 100
            Layout.preferredWidth: width
            color: "white"
        }


        TextField {
            id: textfield
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.preferredHeight: 40
            Layout.rightMargin: 10
            placeholderText: "search for a song.."
            placeholderTextColor: "darkgrey"
            color: "white"

            onTextChanged: GlobalSingleton.songManager.songModel.filterString = text

            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }

        }

        ListView {
            id: songsListView

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10
            clip:true

            spacing: 5

            property int highlightedIndex: -1


            ScrollBar.vertical: ScrollBar {
                id:songScrollbar
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

            model: GlobalSingleton.songManager.songModel// This is the model exposed from C++
            delegate: SongDelegate{
                id: songDelegate

                songDelegateHeight: 63
                songDelegateWidth: songsListView.width - songScrollbar.width - 10
                highlightedIndex: songsListView.highlightedIndex

                onSongDelegateDoubleClicked: {
                    //NowPlaying.playNow(songObject)
                    GlobalSingleton.playbackManager.nowPlaying.playNow(songObj)
                }

                onSongDelegateRightClicked: {
                    songsListView.interactive = false
                    contextMenu.currDelegate = songsListView.itemAtIndex(index)
                    contextMenu.openContextMenu(songObj)
                }
            }

            SongContextMenu{
                id: contextMenu
                property SongDelegate currDelegate

                onPopupClosed: {
                    if(currDelegate){
                        songsListView.interactive = true
                        currDelegate.overlay = "transparent"
                        currDelegate.isContextMenuOpen = false
                    }
                }

            }



    }
    }



}
