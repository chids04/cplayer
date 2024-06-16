import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import com.c.MediaController
import com.c.ViewController
import com.c.SongView
import com.c.AlbumView

Rectangle{

    id: mainWindow
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "transparent"

    Connections{
        target: ViewController

        function onSongViewSelected(){
            viewLoader.source = "Songs.qml"
        }

        function onAlbumViewSelected(){
            viewLoader.source = "Albums.qml"
        }

        function onAlbumSelected(){
            viewLoader.source = "AlbumSongs.qml"
        }

        function onFoldersViewSelected(){
            viewLoader.source = "Folders.qml"
        }

        function onPlaylistsViewSelected(){
            viewLoader.source = "Playlists.qml"
        }

        function onPlaylistSelected(){
            viewLoader.source = "PlaylistSongs.qml"
        }

    }

    RowLayout {
        anchors.fill: parent
        spacing: 15
        Sidebar{

        }

        Loader {
            id: viewLoader
            source: "Folders.qml"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
