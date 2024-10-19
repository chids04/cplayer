import QtQuick 2.15
import QtQuick.Controls 2.15

import cplayer

Menu {
    id: mainMenu
    title: qsTr("Tools")

    property var songObj

    MenuItem{
        id: queueNext
        text: "Queue Next"

        onTriggered: {
            MusicHandler.nowPlaying.queueNext(songObj)
        }
    }

    Menu {
        id: addToPlaylistMenu
        title: "Add to playlist"
        Instantiator {
            id: playlistInstantiator
            model: ModelHandler.playlistList // Assuming PlaylistModel is exposed from C++

            delegate: MenuItem {
                id: menuItemDelegate
                text: playlistName
                onTriggered: {
                    MusicHandler.playlistManager.addSongToPlaylist(playlistID, songObj)
                }
            }

            onObjectAdded: (index, object) => addToPlaylistMenu.insertItem(index, object)
            onObjectRemoved: (index, object) => addToPlaylistMenu.removeItem(object)
        }
    }

    enter: Transition {
                ParallelAnimation {
                    id: popIn
                    PropertyAnimation {
                        //target: [mainMenu, addToPlaylistMenu]
                        target: mainMenu
                        property: "scale"
                        from: 0.9
                        to: 1
                        duration: 50
                    }
                    PropertyAnimation {
                        //target: [mainMenu, addToPlaylistMenu]
                        target: mainMenu
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
                        //target: [mainMenu, addToPlaylistMenu]
                        target: mainMenu
                        property: "scale"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                    PropertyAnimation {
                        //target: [mainMenu, addToPlaylistMenu]
                        target: mainMenu
                        property: "opacity"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                }
            }

    function openContextMenu(song){
        songObj = song
        mainMenu.popup()

    }

}

