import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import com.c.MediaController
import com.c.SongModel

import "./components"


Item {
    id:songsWindow
    // Layout.fillHeight: true
    // Layout.fillWidth: true


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

        // Component {
        //     id:songDelegate

        //     Rectangle {
        //         id: songRect
        //         width: songsListView.width-23
        //         height: 80
        //         radius: 10
        //         color: index % 2 == 0 ? "#1e1f20" : "#131314"

        //         MouseArea {
        //             anchors.fill: parent
        //             onDoubleClicked: {
        //                 MediaPlayerController.setSong(filePath, title, artist, album, features)
        //             }
        //         }

        //         RowLayout {

        //             anchors{
        //                 fill: parent
        //             }
        //             spacing:0

        //             Item {
        //                 Layout.preferredWidth: parent.width * 0.33
        //                 Layout.preferredHeight: parent.height

        //                 RowLayout{
        //                     anchors.fill: parent
        //                     spacing: 0

        //                     Image {
        //                         width:60
        //                         height:60
        //                         source: "image://coverArt/" + album + "/" + artist
        //                         sourceSize.width: 60
        //                         sourceSize.height: 60
        //                         Layout.rightMargin: 10
        //                         Layout.leftMargin: 10
        //                     }

        //                     Text {
        //                         //text: features[0] != "" ? artist + "feat. " + features.join(", ") : artist
        //                         text: title
        //                         font.bold: true
        //                         color: "white"
        //                     }

        //                     Item{
        //                         Layout.fillWidth: true
        //                     }


        //                 }


        //             }

        //             Item{
        //                 Layout.preferredWidth: parent.width * 0.33
        //                 Layout.preferredHeight: parent.height

        //                 Text {
        //                     color: "white"
        //                     text: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
        //                     anchors.centerIn: parent
        //                 }
        //             }



        //             Item{
        //                 Layout.preferredWidth: parent.width * 0.33
        //                 Layout.preferredHeight: parent.height

        //                 Text {
        //                     text: album
        //                     color: "white"
        //                     anchors.centerIn: parent
        //                 }
        //             }


        //         }


        //     }
        // }

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
