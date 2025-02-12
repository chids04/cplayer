pragma ComponentBehavior: Bound

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
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.preferredHeight: 40
            Layout.rightMargin: 10
            placeholderText: "search for an album.."
            placeholderTextColor: "darkgrey"
            color: "white"

            onTextChanged: GlobalSingleton.songManager.albumSearchModel.filterString = text

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


            Component{
                id: albumDelegate

                Rectangle{
                    id: albumCard
                    width: gridView.cellWidth - gridViewScrollbar.width
                    height: gridView.cellHeight
                    color: "transparent"
                    radius: 10

                    required property string albumName
                    required property var albumObjRole
                    required property list<string> albumArtists

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
                            GlobalSingleton.songManager.setAlbum(albumCard.albumObjRole)
                            GlobalSingleton.viewController.selectAlbum()
                        }

                    }

                    ColumnLayout{
                        spacing: 0
                        anchors.fill: parent
                        anchors.bottomMargin: 5

                        Image {
                            source: "image://coverArt/" + albumCard.albumName + "/" + albumCard.albumArtists.join('%')
                            sourceSize.width: albumCard.width - 100
                            sourceSize.height: albumCard.width - 100
                            Layout.alignment: Qt.AlignHCenter
                            asynchronous: true
                        }

                        Text {
                            text: albumCard.albumName
                            font.bold: true
                            font.pointSize: 16
                            Layout.leftMargin: 5
                            Layout.rightMargin: 5
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            elide: Text.ElideRight
                        }

                        Text {
                            text: albumCard.albumArtists.join(", ")
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                            Layout.leftMargin: 5
                            Layout.rightMargin: 5
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            elide: Text.ElideRight
                        }
                    }
                }
            }

            model: GlobalSingleton.songManager.albumSearchModel
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
