import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import com.c.AlbumFilterProxyModel
import com.c.AlbumSongsView
import com.c.MediaController
import com.c.PlaylistManager

import "./components"


Item {
    anchors.fill: parent
    anchors.topMargin: 20




    ColumnLayout{
        anchors.fill: parent

        Rectangle{
            id: albumInfo
            Layout.preferredHeight: parent.height * 0.3
            Layout.fillWidth: true

            color: "transparent"
            clip: true



            RowLayout{
                anchors.fill: parent
                spacing: 10
                Image{
                    id: albumCoverArt
                    Layout.preferredHeight: parent.height - 10
                    Layout.preferredWidth: parent.height - 10

                    source: "image://coverArt/" + AlbumSongsView.albumName + "/" + AlbumSongsView.albumArtists[0]
                    sourceSize.width: parent.height - 10
                    sourceSize.height: parent.height - 10

                }

                ColumnLayout{
                    Layout.fillHeight: true


                    Text{
                        id: loadedAlbumName
                        color: "white"
                        text: AlbumSongsView.albumName
                        font.bold: true
                        font.pointSize: 40


                    }

                    Text{
                        id: loadedAlbumArtists
                        text: AlbumSongsView.albumArtists.join(", ")
                        color:"white"
                        font.pointSize: 20
                    }

                    Text{
                        id: loadedAlbumGenre
                        text: AlbumSongsView.genre
                        color: "white"
                        font.pointSize: 10
                    }

                    Text{
                        id: loadedAlbumYear
                        text: AlbumSongsView.year
                        color: "white"
                        font.pointSize: 10
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
            id: albumControls

            CButton{
                id: playAlbumBtn
                buttonText: "Play Album"

                onButtonClicked: {
                    PlaylistManager.playAlbum(AlbumSongsView.albumName, AlbumSongsView.albumArtists);
                }

            }


        }

        Rectangle{
            id: songList
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: playAlbumBtn.height

            color: "transparent"
            ListView {
                id: albumSongsListView
                anchors.fill: parent
                anchors.topMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 10
                clip: true

                ScrollBar.vertical: ScrollBar {
                    id:albumScrollBar
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

                model: AlbumFilterModel

                delegate: SongDelegate{
                    id: songDelegate

                    songDelegateHeight: 80
                    songDelegateWidth: albumSongsListView.width - 23
                    songDelegateColor: index % 2 == 0 ? "#1e1f20" : "#131314"

                    songDelegateNumber: albumNum
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
    }
}
