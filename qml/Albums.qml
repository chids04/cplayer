import QtQuick
import QtQuick.Controls

import com.c.AlbumListModel
import com.c.ViewController
import com.c.AlbumViewController
import com.c.AlbumFilterProxyModel

Item {
    anchors.fill: parent;

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

    GridView {
        id: gridView
        anchors.fill: parent
        cellWidth: itemWidth
        cellHeight: itemWidth


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
                        AlbumFilterModel.setAlbumName(albumName)
                        AlbumController.setAlbum(albumArtists, albumName, albumGenre, albumYear, albumSongCount)
                        ViewController.selectAlbum()
                    }

                }

                Column{
                    spacing: 5
                    anchors.centerIn: parent

                    Image {
                        source: "image://coverArt/" + albumName + "/" + albumArtists[0]
                        sourceSize.width: albumCard.width - 100
                        sourceSize.height: albumCard.width - 100
                    }

                    Text {
                        text: albumName
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        color: "white"
                    }

                    Text {
                        text: albumArtists[0]
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        color: "white"
                    }
                }
            }
        }

        model: AlbumModel
        delegate: albumDelegate

        onWidthChanged: {
            resizeTimer.restart()

        }
        onHeightChanged: {
            resizeTimer.restart()
        }

    }
}
