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
            console.log("song view selected")
            stackView.push("Songs.qml")
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

        Sidebar{
        }

        StackView{
            id: stackView
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true

            pushEnter: null
            pushExit: null

            Component.onCompleted:{
                stackView.push("Songs.qml")
            }

        }
    }
}


