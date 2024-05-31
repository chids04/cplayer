import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import com.c.MediaController
import com.c.ViewController

Rectangle{

    id: mainWindow
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "transparent"

    Connections{
        target: ViewController

        function onSongViewSelected(){
            console.log("switching to song view")
            viewLoader.source = "Songs.qml"
            console.log(viewLoader.active)
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

    }

    RowLayout {
        anchors.fill: parent
        spacing: 15
        Sidebar{

        }

        Loader {
            id: viewLoader
            source: "Songs.qml"
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
