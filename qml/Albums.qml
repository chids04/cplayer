import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import cplayer

Item {
    id: albumWindow

    property int minColumns: 5
    property int maxColumns: 5
    property real itemWidth: Math.max(gridView.width / maxColumns, gridView.width / minColumns)

    Timer {
        id: resizeTimer
        interval: 200
        repeat: false
        onTriggered: {
            itemWidth = Math.max(gridView.width / maxColumns, gridView.width / minColumns)
            gridView.cellWidth = itemWidth
            gridView.cellHeight = itemWidth

        }
    }

    ColumnLayout {
        anchors.fill: parent

        Text {
            text: "albums"
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
            placeholderText: "search for an album.."
            placeholderTextColor: "darkgrey"
            color: "white"

            onTextChanged: ModelHandler.albumList.filterString = text

            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }

        }

        GridView {
            id: gridView
//            anchors.fill: parent
//            anchors.rightMargin: 10
//            anchors.leftMargin: 10
            Layout.fillHeight: true
            Layout.fillWidth: true

            cellWidth: itemWidth
            cellHeight: itemWidth
            clip: true


            Component{
                id: albumDelegate

                Rectangle{
                    id: albumCard
                    width: gridView.cellWidth
                    height: gridView.cellHeight
                    color: "transparent"
                    radius: 10

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            albumCard.color = "#0b0b0b"

                        }
                        onExited: {
                            albumCard.color = "transparent"
                        }

                        onDoubleClicked:{
                            //AlbumFilterModel.setAlbumName(albumName)
                            ViewController.albumSongsView.setAlbum(albumArtists, albumName, albumGenre, albumYear, albumSongCount)
                            ModelHandler.albumSongs.setCurrentAlbumName(albumName)
                            ViewController.selectAlbum()
                        }

                    }

                    ColumnLayout{
                        spacing: 0
                        anchors.fill: parent
                        anchors.bottomMargin: 5

                        Image {
                            source: "image://coverArt/" + albumName + "/" + albumArtists.join('%')
                            sourceSize.width: albumCard.width - 100
                            sourceSize.height: albumCard.width - 100
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Text {
                            text: albumName
                            font.bold: true
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            elide: Text.ElideRight
                        }

                        Text {
                            text: albumArtists[0]
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            elide: Text.ElideRight
                        }
                    }
                }
            }

            model: ModelHandler.albumList
            delegate: albumDelegate

            onWidthChanged: {
                resizeTimer.restart()

            }
            onHeightChanged: {
                resizeTimer.restart()
            }

        }
    }


}
