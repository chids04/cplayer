pragma ComponentBehavior: Bound
import QtQuick 2.15
import QtQuick.Controls 2.15

import cplayer

Menu {
    id: playlistMenu
    title: qsTr("Tools")

    property int playlistID
    property string playlistName
    property bool playlistHasCover

    EditPlaylist{
        id: editPopup
    }

    MenuItem{
        id: removePlaylist
        text: "remove playlist"

        onTriggered: {
            GlobalSingleton.playlistManager.removePlaylist(playlistMenu.playlistID)
        }
    }

    MenuItem{
        id: modify
        text: "modify playlist"

        onTriggered: {
            editPopup.openPopup(playlistMenu.playlistID, playlistMenu.playlistName, playlistMenu.playlistHasCover)
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

    function openContextMenu(id, name, hasCover){
        playlistID = id
        playlistName = name
        playlistHasCover = hasCover
        playlistMenu.popup()

    }

}

