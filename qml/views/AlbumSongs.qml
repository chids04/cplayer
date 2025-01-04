import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import cplayer

import "../components"

Item {

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Item{
            id: albumInfo
            Layout.preferredHeight: parent.height * 0.3
            Layout.fillWidth: true
            Layout.topMargin: 10

            clip: true



            RowLayout{
                anchors.fill: parent
                spacing: 10
                Image{
                    id: albumCoverArt

                    source: "image://coverArt/" + ViewController.albumSongsView.albumName + "/" + ViewController.albumSongsView.albumArtists[0]
                    sourceSize.width: 170
                    sourceSize.height: 170

                }

                ColumnLayout{
                    Layout.fillHeight: true


                    Text{
                        id: loadedAlbumName
                        color: "white"
                        text: ViewController.albumSongsView.albumName
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                        font.bold: true
                        font.pointSize: 40

                    }

                    Text{
                        id: loadedAlbumArtists
                        text: ViewController.albumSongsView.albumArtists.join(", ")
                        color:"white"
                        font.pointSize: 20
                    }

                    Text{
                        id: loadedAlbumGenre
                        text: ViewController.albumSongsView.genre
                        color: "white"
                        font.pointSize: 10
                    }

                    Text{
                        id: loadedAlbumYear
                        text: ViewController.albumSongsView.year
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

        RowLayout{
            id: albumControls

            CButton{
                id: playAlbumBtn
                buttonText: "Play Now"

                onButtonClicked: {
                    MusicHandler.nowPlaying.playAlbum(ViewController.albumSongsView.albumName, ViewController.albumSongsView.albumArtists, false);
                }

            }

            CButton{
                id: queueAlbumBtn
                buttonText: "Add to Queue"

                onButtonClicked: {
                    MusicHandler.nowPlaying.playAlbum(ViewController.albumSongsView.albumName, ViewController.albumSongsView.albumArtists, true);
                    let albumNameBold = "<b>" + ViewController.albumSongsView.albumName + "</b>";
                    ViewController.showMsg(albumNameBold + " added to queue")
                }
            }


        }

        Rectangle{
            id: songList
            Layout.fillHeight: true
            Layout.fillWidth: true

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

                model: ModelHandler.albumSongs

                delegate: SongDelegate{
                    id: songDelegate

                    songDelegateIndex: index
                    songDelegateHeight: 80
                    songDelegateWidth: albumSongsListView.width - 23
                    songDelegateColor: index % 2 == 0 ? "#1e1f20" : "#131314"

                    songObj: songObject
                    songDelegateNumber: albumNum
                    songDelegateTitle: title
                    songDelegateAuthors: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
                    songDelegateAlbum: album
                    songDelegateLeadingArtist: artist
                    songFeatures: albumArtists

                    onSongDelegateDoubleClicked: {
                        MusicHandler.nowPlaying.playNow(songObject)
                    }

                }

            }



        }
    }
}

