import QtQuick 2.15
import QtQuick.Controls 2.15

import cplayer

Menu {
    id: playlistMenu
    title: qsTr("Tools")

    property int playlistID

    MenuItem{
        id: removePlaylist
        text: "Remove Playlist"

        onTriggered: {
            MusicHandler.playlistManager.removePlaylist(playlistID)
        }
    }


    enter: Transition {
                ParallelAnimation {
                    id: popIn
                    PropertyAnimation {
                        target: playlistMenu
                        property: "scale"
                        from: 0.9
                        to: 1
                        duration: 50
                    }
                    PropertyAnimation {
                        target: playlistMenu
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
                        target: playlistMenu
                        property: "scale"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                    PropertyAnimation {
                        target: playlistMenu
                        property: "opacity"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                }
            }

    function openContextMenu(playlist){
        playlistID = playlist
        playlistMenu.popup()

    }

}

