pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Effects

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
            albumWindow.itemWidth = Math.max(gridView.width / albumWindow.maxColumns, gridView.width / albumWindow.minColumns)
            gridView.cellWidth = albumWindow.itemWidth
            gridView.cellHeight = albumWindow.itemWidth

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
            id: searchField
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.preferredHeight: 40
            Layout.rightMargin: 10
            placeholderText: "search for an album.."
            placeholderTextColor: "darkgrey"
            color: "white"

            onTextChanged: debounceTimer.restart()

            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }

            Timer {
                id: debounceTimer
                interval: 500  // delay in milliseconds
                repeat: false
                onTriggered: {
                    // Update the filter string after the delay expires.
                    GlobalSingleton.songManager.albumSearchModel.filterString = searchField.text
                }
            }


        }

        GridView {
            id: gridView
//            anchors.fill: parent
//            anchors.rightMargin: 10
//            anchors.leftMargin: 10
            Layout.fillHeight: true
            Layout.fillWidth: true

            cellWidth: albumWindow.itemWidth
            cellHeight: albumWindow.itemWidth
            clip: true

            ScrollBar.vertical: ScrollBar {
                id:gridViewScrollbar
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


            

            model: GlobalSingleton.songManager.albumSearchModel
            delegate: AlbumDelegate{
                itemWidth: gridView.cellWidth - gridViewScrollbar.width
                itemHeight: gridView.cellHeight
            }

            onWidthChanged: {
                //resizeTimer.restart()

            }
            onHeightChanged: {
                //resizeTimer.restart()
            }

        }
    }


}
