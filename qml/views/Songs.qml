pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import cplayer


Item {
    id:songsWindow

    ColumnLayout{
        anchors.fill: parent

        Text{
            text: "songs"
            font.bold: true
            font.pointSize: 100
            Layout.preferredWidth: width
            color: "white"
        }


        TextField {
            id: textfield
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.preferredHeight: 40
            Layout.rightMargin: 10
            placeholderText: "search for a song.."
            placeholderTextColor: "darkgrey"
            color: "white"

            onTextChanged: GlobalSingleton.songManager.songModel.filterString = text

            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }

        }

        GridView {
            id: songsListView

            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: (Math.floor(parent.width / cellWidth)) * cellWidth



            Layout.topMargin: 10

            clip: true
            cellWidth: 200
            cellHeight: 100


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

            model: GlobalSingleton.songManager.songModel// This is the model exposed from C++
            delegate: SongViewDelegate{
                id: songDelegate

                required property int index
                required property string title
                required property string artist
                required property list<string> features
                required property string album
                required property list<string> albumArtists
                required property var songObject

                songDelegateHeight: 80
                songDelegateWidth: 180
                songDelegateColor: index % 2 == 0 ? "#1e1f20" : "#131314"
                songObj: songObject

                songDelegateTitle: title
                songDelegateAuthors: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
                songDelegateAlbum: album
                songDelegateLeadingArtist: artist
                songFeatures: albumArtists

                onSongDelegateDoubleClicked: {
                    //NowPlaying.playNow(songObject)
                    GlobalSingleton.playbackManager.nowPlaying.playNow(songObject)
                }

            }


    }
    }



}
