import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import com.c.AlbumListModel
import com.c.ViewController
import com.c.AlbumSongsView
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
        anchors.rightMargin: 10
        anchors.leftMargin: 10
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
                        AlbumSongsView.setAlbum(albumArtists, albumName, albumGenre, albumYear, albumSongCount)
                        ViewController.selectAlbum()
                    }

                }

                ColumnLayout{
                    spacing: 0
                    anchors.fill: parent
                    anchors.bottomMargin: 5

                    Image {
                        source: "image://coverArt/" + albumName + "/" + albumArtists[0]
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
                    }

                    Text {
                        text: albumArtists[0]
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                        color: "white"
                        Layout.alignment: Qt.AlignHCenter
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
