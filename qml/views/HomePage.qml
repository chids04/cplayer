pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Effects

import cplayer

Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "#131314"
    topRightRadius: 20

    Rectangle {
        id: albumSlide
        width: parent.width / 4
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }

        color: "#232425"

        TextField {
            id: textfield
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                topMargin: 10
                leftMargin: 20
                rightMargin: 20
            }

            onTextChanged: GlobalSingleton.songManager.albumSearchModel.filterString = text

            height: 40

            placeholderText: "search for an album"
            placeholderTextColor: "darkgrey"
            color: "white"

            background: Rectangle {
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }
        }

        ListView {
            id: albumListView
            width: parent.width - 70 + 15

            anchors {
                topMargin: 10
                top: textfield.bottom
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }

            clip: true

            Component {
                id: albumDelegate
                Item {
                    id: albumCard

                    width: albumListView.width
                    height: albumListView.width

                    function sayHello() {
                        console.log("hello")
                    }

                    Behavior on scale {
                        NumberAnimation {
                            duration: 200
                            easing.type: Easing.OutBack
                        }
                    }
                    states: [
                            State {
                                name: "doubleClicked"
                                PropertyChanges {
                                    albumCard{
                                        scale: 0.95
                                    }
                                }
                            }
                        ]

                    transitions: [
                            Transition {
                                from: ""
                                to: "doubleClicked"
                                reversible: true
                                property int timesRun: 0

                                NumberAnimation {
                                    target: albumCard
                                    property: "scale"
                                    duration: 200
                                    easing.type: Easing.OutBack
                                }

                                onRunningChanged: {
                                    timesRun++
                                    if (!running) {
                                        if(timesRun == 4){
                                            timesRun = 0
                                            GlobalSingleton.songManager.setAlbum(albumCard.albumObjRole)
                                            GlobalSingleton.viewController.selectAlbum()
                                        }
                                    }
                                }
                            }
                        ]

                    Rectangle {
                        id: overlay
                        anchors.fill: parent
                        color : "#121212"
                        radius: 10
                        opacity : 0

                        Behavior on opacity {
                            NumberAnimation{
                                duration: 200
                            }
                        }
                    }
                    property alias albumImgWidth: albumImage.sourceSize.width
                    property alias albumImgHeight: albumImage.sourceSize.height

                    required property string albumName
                    required property var albumObjRole
                    required property list<string> albumArtists

                    property bool firstLoad: true

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: {
                            overlay.opacity = 0.5
                        }
                        onExited: {
                            overlay.opacity = 0
                        }

                        onReleased: {
                            albumCard.state = ""
                        }

                        onDoubleClicked: {
                            albumCard.state = "doubleClicked"
                            //GlobalSingleton.songManager.setAlbum(albumCard.albumObjRole)
                            //GlobalSingleton.viewController.selectAlbum()
                        }
                    }

                    ColumnLayout {
                        spacing: 0
                        anchors.fill: parent

                        Image {
                            id: albumImage
                            source: "image://coverArt/" + albumCard.albumName + "/" + albumCard.albumArtists.join("++?")
                            property bool firstLoad: true

                            sourceSize.width: 200
                            sourceSize.height: 200
                            Layout.preferredHeight: albumCard.width - 80
                            Layout.preferredWidth: albumCard.width - 80
                            asynchronous: true

                            Layout.alignment: Qt.AlignHCenter

                            layer.enabled: true
                            layer.effect: MultiEffect {
                                source: albumImage
                                x: albumImage.x
                                y: albumImage.y
                                width: albumImage.width
                                height: albumImage.height
                                autoPaddingEnabled: true
                                shadowEnabled: true
                                shadowVerticalOffset: 10
                                shadowHorizontalOffset: 12  
                            }
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
        }
    }

    TextField {
        id: songSearchField
        height: 40

        anchors {
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
        onTextChanged: GlobalSingleton.songManager.songModel.filterString = text

        background: Rectangle {
            border.color: "#343434"
            border.width: 2
            color: "#232425"
            radius: 10
        }
    }

    ListView {
        id: songsListView

        anchors {
            topMargin: 20
            leftMargin: 10
            left: albumSlide.right
            right: parent.right
            top: songSearchField.bottom
            bottom: parent.bottom
        }

        clip: true

        spacing: 5

        property int highlightedIndex: -1

        ScrollBar.vertical: ScrollBar {
            id: songScrollbar
            policy: ScrollBar.AlwaysOn

            width: 15

            contentItem: Rectangle {
                implicitWidth: 15
                radius: 3
                color: "#606060"
            }

            background: Rectangle {
                color: "transparent"
            }
        }

        model: GlobalSingleton.songManager.songModel
        delegate: SongDelegate {
            id: songDelegate

            songDelegateHeight: 63
            songDelegateWidth: songsListView.width - songScrollbar.width - 10
            highlightedIndex: songsListView.highlightedIndex

            onSongDelegateDoubleClicked: {
                GlobalSingleton.playbackManager.nowPlaying.playNow(songObj)
            }

            onSongDelegateRightClicked: {
                songsListView.interactive = false
                contextMenu.currDelegate = songsListView.itemAtIndex(index)
                contextMenu.openContextMenu(songObj)
            }
        }

        SongContextMenu {
            id: contextMenu
            property SongDelegate currDelegate

            onPopupClosed: {
                if (currDelegate) {
                    songsListView.interactive = true
                    currDelegate.overlay = "transparent"
                    currDelegate.isContextMenuOpen = false
                }
            }
        }
    }
}
