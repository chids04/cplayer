import QtQuick 2.15
import QtQuick.Controls 2.15
import com.c.PlaylistModel

Menu {
    id: mainMenu
    title: qsTr("Tools")

    Menu {
        id: addToPlaylistMenu
        title: "Add to playlist"
        Instantiator {
            id: playlistInstantiator
            model: PlaylistModel  // Assuming PlaylistModel is exposed from C++

            delegate: MenuItem {
                text: playlistName  // Assuming playlistName is the role in PlaylistModel
                //onTriggered: addToPlaylist(model.playlistName)
                onTriggered: {

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
                        target: popup
                        property: "scale"
                        from: 0.9
                        to: 1
                        duration: 50
                    }
                    PropertyAnimation {
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
                        target: mainMenu
                        property: "scale"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                    PropertyAnimation {
                        target: popup
                        property: "opacity"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                }
            }



}

