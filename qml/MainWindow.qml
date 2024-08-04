import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

//import com.c.ViewController
//import com.c.SongView
//import com.c.AlbumView

import cplayer

Rectangle{

    id: mainWindow
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "transparent"

    Connections{
        target: ViewController

        function onSongViewSelected(){
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
    }

    RowLayout {
        anchors.fill: parent
        spacing: 15

        Sidebar{
        }

        StackView{
            id: stackView
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true

            pushEnter: null
            pushExit: null

        }

//        Loader {
//            id: viewLoader
//            source: "Folders.qml"
//            Layout.fillWidth: true
//            Layout.fillHeight: true
//        }

    }
}


