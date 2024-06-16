import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import com.c.MediaController
import com.c.SongModel

import "./components"


Item {
    id:songsWindow

    ListView {
        id: songsListView
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10

        ScrollBar.vertical: ScrollBar {
            id:songScollbar
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

        model: SongModel// This is the model exposed from C++
        delegate: SongDelegate{
            id: songDelegate
            songDelegateHeight: 80
            songDelegateWidth: songsListView.width - 23
            songDelegateColor: index % 2 == 0 ? "#1e1f20" : "#131314"

            songDelegateNumber: index + 1
            songDelegateTitle: title
            songDelegateAuthors: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
            songDelegateAlbum: album
            songDelegateLeadingArtist: artist

            onSongDelegateDoubleClicked: {
                MediaPlayerController.setSong(filePath, title, artist, album, features)
            }

        }

        
    }

}
