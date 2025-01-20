pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import cplayer

import "../components"

Item {

    ColumnLayout{
        anchors.fill: parent

        Item{
            id: playlistInfo
            Layout.preferredHeight: parent.height * 0.3
            Layout.fillWidth: true
            Layout.topMargin: 10

            clip: true



            RowLayout{
                anchors.fill: parent
                spacing: 10
                Image{
                    id: playlistCoverArt
                    Layout.preferredHeight: parent.height - 10
                    Layout.preferredWidth: parent.height - 10

                    source: GlobalSingleton.playlistManager.hasCover ? "image://playlistCovers" + "/" + GlobalSingleton.playlistManager.playlistID : "qrc:/resource/ui/assets/unknownCover.png"
                    sourceSize.width: parent.height - 10
                    sourceSize.height: parent.height - 10
                    cache: false

                }

                ColumnLayout{
                    Layout.fillHeight: true


                    Text{
                        id: loadedPlaylistName
                        color: "white"
                        text: GlobalSingleton.playlistManager.playlistName
                        font.bold: true
                        font.pointSize: 40


                    }

                }

                Rectangle{ //filler item
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                }
            }
        }
        RowLayout{

            CButton{
                id: playPlaylistBtn
                buttonText: "Play Playlist"

                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playPlaylist(GlobalSingleton.playlistManager.currentPlaylist)

                }

            }

            CButton{
                id: queuePlaylistBtn
                buttonText: "Queue Playlist"

                onButtonClicked: {
                    GlobalSingleton.playbackManager.nowPlaying.playPlaylist(GlobalSingleton.playlistManager.currentPlaylist, true)
                }
            }
        }


        Rectangle{
            id: songList
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: playPlaylistBtn.height

            color: "transparent"
            ListView {
                id: playlistSongsListView
                anchors.fill: parent
                anchors.topMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 10
                clip: true

                ScrollBar.vertical: ScrollBar {
                    id:playlistScrollBar
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

                //model: PlaylistView.playlistSongsModel
                model: GlobalSingleton.playlistManager.playlistSongs

                delegate: SongDelegate{
                    id: songDelegate

                    required property int index
                    required property string title
                    required property string album
                    required property string artist
                    required property list<string> features
                    required property list<string> albumArtists
                    required property var songObject

                    songDelegateIndex: index
                    songDelegateHeight: 80
                    songDelegateWidth: playlistSongsListView.width - 23
                    songDelegateColor: index % 2 == 0 ? "#1e1f20" : "#131314"

                    songDelegateNumber: index + 1
                    songDelegateTitle: title
                    songDelegateAuthors: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
                    songDelegateAlbum: album
                    songDelegateLeadingArtist: artist
                    songFeatures: albumArtists

                    onSongDelegateDoubleClicked: {
                        GlobalSingleton.playbackManager.nowPlaying.playNow(songObject)
                    }

                }

            }



        }
    }
}
