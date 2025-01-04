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
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.preferredHeight: 40
            Layout.rightMargin: 10
            placeholderText: "search for a song.."
            placeholderTextColor: "darkgrey"
            color: "white"

            onTextChanged: ModelHandler.songList.filterString = text

            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }

        }

        ListView {
            id: songsListView

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 10
            spacing: 5

            clip: true

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

            model: ModelHandler.songList// This is the model exposed from C++
            delegate: SongDelegate{
                id: songDelegate
                songDelegateIndex: index
                songDelegateHeight: 80
                songDelegateWidth: songsListView.width - 23
                songDelegateColor: index % 2 == 0 ? "#1e1f20" : "#131314"
                songObj: songObject

                songDelegateNumber: index + 1
                songDelegateTitle: title
                songDelegateAuthors: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
                songDelegateAlbum: album
                songDelegateLeadingArtist: artist
                songFeatures: albumArtists

                onSongDelegateDoubleClicked: {
                    //NowPlaying.playNow(songObject)
                    MusicHandler.nowPlaying.playNow(songObject)
                }

            }


    }
    }



}
