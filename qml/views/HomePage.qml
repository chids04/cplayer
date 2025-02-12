pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import cplayer

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "#131314"
    topRightRadius: 20

    Rectangle{
        id: albumSlide
        width: parent.width/4
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }

        color: "#232425"


        TextField {
            id: textfield
            anchors{
                left: parent.left
                right: parent.right
                top: parent.top
                topMargin: 10
                leftMargin: 20
                rightMargin: 20
            }
            height: 40

            placeholderText: "search for an album"
            placeholderTextColor: "darkgrey"
            color: "white"


            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }

        }


        ListView {
            id: albumListView
//            anchors.fill: parent
//            anchors.rightMargin: 10
//            anchors.leftMargin: 10
            width: parent.width-70+15



            anchors {
                topMargin: 10
                top: textfield.bottom
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter

            }
            clip: true

            Component{
                id: albumDelegate

                Rectangle{
                    id: albumCard
                    color: "transparent"
                    radius: 10

                    width: albumListView.width
                    height: albumListView.width


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

                        Image {
                            source: "image://coverArt/" + albumCard.albumName + "/" + albumCard.albumArtists.join('%')
                            // sourceSize.width: albumCard.width - 80
                            // sourceSize.height: albumCard.width - 80

                            sourceSize.width: 100
                            sourceSize.height: 100
                            Layout.alignment: Qt.AlignHCenter
                            asynchronous: true
                        }

                        Text {
                            text: albumCard.albumName
                            font.bold: true
                            font.pointSize: 16
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                            Layout.fillWidth: true
                            Layout.leftMargin: 5
                            Layout.rightMargin: 5
                            horizontalAlignment: Text.AlignHCenter
                            elide: Text.ElideRight
                        }

                        Text {
                            text: albumCard.albumArtists.join(", ")
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                            Layout.fillWidth: true
                            Layout.bottomMargin: 5
                            Layout.leftMargin: 5
                            Layout.rightMargin: 5
                            horizontalAlignment: Text.AlignHCenter
                            elide: Text.ElideRight
                        }
                    }
                }
            }

            model: GlobalSingleton.songManager.albumSearchModel
            delegate: albumDelegate

            // onWidthChanged: {
            //     resizeTimer.restart()

            // }
            // onHeightChanged: {
            //     resizeTimer.restart()
            // }

        }

    }

    TextField {
        id: songSearchField
        height: 40

        anchors{
            left: albumSlide.right
            right: parent.right
            top: parent.top
            topMargin: 20
            leftMargin: 60
            rightMargin: 60
        }

        placeholderText: "search for a song"
        placeholderTextColor: "darkgrey"
        color: "white"


        background: Rectangle{
            border.color: "#343434"
            border.width: 2
            color: "#232425"
            radius: 10
        }

    }
    ListView {
        id: songsListView

        anchors{
            topMargin: 20
            leftMargin: 10
            left: albumSlide.right
            right: parent.right
            top: songSearchField.bottom
            bottom: parent.bottom
        }

        clip:true

        spacing: 5

        property int highlightedIndex: -1


        ScrollBar.vertical: ScrollBar {
            id:songScrollbar
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

        model: GlobalSingleton.songManager.songModel// This is the model exposed from C++
        delegate: SongDelegate{
            id: songDelegate

            songDelegateHeight: 63
            songDelegateWidth: songsListView.width - songScrollbar.width - 10
            highlightedIndex: songsListView.highlightedIndex

            onSongDelegateDoubleClicked: {
                //NowPlaying.playNow(songObject)
                GlobalSingleton.playbackManager.nowPlaying.playNow(songObj)
            }

            onSongDelegateRightClicked: {
                songsListView.interactive = false
                contextMenu.currDelegate = songsListView.itemAtIndex(index)
                contextMenu.openContextMenu(songObj)
            }
        }

        SongContextMenu{
            id: contextMenu
            property SongDelegate currDelegate

            onPopupClosed: {
                if(currDelegate){
                    songsListView.interactive = true
                    currDelegate.overlay = "transparent"
                    currDelegate.isContextMenuOpen = false
                }
            }

        }



    }

}
