import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import com.c.AlbumFilterProxyModel
import com.c.AlbumSongsView
import com.c.MediaController
import com.c.PlaylistView

import "./components"

Item {
    anchors.fill: parent
    anchors.topMargin: 20

    ColumnLayout{
        anchors.fill: parent

        Rectangle{
            id: playlistInfo
            Layout.preferredHeight: parent.height * 0.3
            Layout.fillWidth: true

            color: "transparent"
            clip: true



            RowLayout{
                anchors.fill: parent
                spacing: 10
                Image{
                    id: playlistCoverArt
                    Layout.preferredHeight: parent.height - 10
                    Layout.preferredWidth: parent.height - 10

                    source: PlaylistView.hasCover ? "img://coverArt" + PlaylistView.playlistName + "/" + PlaylistView.playlistID : "qrc:/resource/ui/assets/unknownCover.png"
                    sourceSize.width: parent.height - 10
                    sourceSize.height: parent.height - 10

                }

                ColumnLayout{
                    Layout.fillHeight: true


                    Text{
                        id: loadedPlaylistName
                        color: "white"
                        text: PlaylistView.playlistName
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

        Item{
            id: playlistControls

            CButton{
                id: playPlaylistBtn
                buttonText: "Play Playlist"

                onButtonClicked: {
                    //PlaylistManager.playAlbum(AlbumSongsView.albumName, AlbumSongsView.albumArtists);
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

                model: PlaylistView.playlistSongsModel

                delegate: SongDelegate{
                    id: songDelegate

                    songDelegateIndex: index
                    songDelegateHeight: 80
                    songDelegateWidth: playlistSongsListView.width - 23
                    songDelegateColor: index % 2 == 0 ? "#1e1f20" : "#131314"

                    songDelegateNumber: index + 1
                    songDelegateTitle: title
                    songDelegateAuthors: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
                    songDelegateAlbum: album
                    songDelegateLeadingArtist: artist

                    onSongDelegateDoubleClicked: {
                        MediaPlayerController.onPlaySong(songObject)
                    }

                }

            }



        }
    }
}
