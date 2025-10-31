import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import cplayer

Item{

    id: mainWindow
    Layout.fillWidth: true
    Layout.fillHeight: true

    Connections{
        target: GlobalSingleton.viewController

        function onSongViewSelected(){
            stackView.push("HomePage.qml")
            //stackView.push("Songs.qml")
        }

        function onAlbumViewSelected(){
            stackView.push("Albums.qml")
        }

        function onAlbumSelected(){
            stackView.push("AlbumSongs.qml")
        }

        function onFoldersViewSelected(){
            stackView.push("Folders.qml")
        }

        function onPlaylistsViewSelected(){
            stackView.push("Playlists.qml")
        }

        function onPlaylistSelected(){
            stackView.push("PlaylistSongs.qml")
        }

        function onSettingsViewSelected(){
            stackView.push("Settings.qml")
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 10


        CSidebar{
            sidebarStackView: stackView
        }

        StackView{
            id: stackView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rightMargin: 5
            clip: true


            pushEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to:1
                    duration: 200
                }
            }
            pushExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to:0
                    duration: 200
                }
            }

            popEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to:1
                    duration: 200
                }
            }
            popExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to:0
                    duration: 200
                }
            }

            Component.onCompleted:{
                stackView.push("HomePage.qml")
            }

        }
    }
}


