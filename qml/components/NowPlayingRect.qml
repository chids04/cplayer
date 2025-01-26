pragma ComponentBehavior: Bound

import QtQuick
import QtQml.Models
import QtQuick.Layouts
import QtQuick.Controls

import cplayer
//![0]
Rectangle {
    id: root

    width: 350
    height: 450

    color: "#303132"
    border.color: "#6e7173"
    border.width: 2
    radius: 5

    Text{
        id: nextUpText
        text: "songs next up..."
        color: "white"
        font.pointSize: 30

        anchors.top: parent.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle{
        id: seperator
        height:1
        anchors {
            topMargin: 10
            top: nextUpText.bottom
            left: parent.left
            right: parent.right
            rightMargin: 10
            leftMargin: 10
        }
    }

    CButton{
        id: clearBtn
        buttonText: "clear queue"
        buttonColor: "#444647"
        anchors{
            topMargin: 10
            top: seperator.bottom
            horizontalCenter: parent.horizontalCenter
        }

        onButtonClicked: GlobalSingleton.playbackManager.nowPlaying.clearQueue()
    }

    Component {
        id: dragDelegate

        MouseArea {
            id: dragArea

            property bool held: false
            required property string title
            required property string artist
            required property string album
            required property list<string> albumArtists
            required property list<string> features

            anchors {
                left: parent?.left
                right: parent?.right
                leftMargin: 10
                rightMargin: viewScrollBar.width + 5
            }
            height: content.height

            drag.target: held ? content : undefined
            drag.axis: Drag.YAxis

            onPressed: held = true
            onReleased: held = false

            onPositionChanged: {
                view.positionViewAtIndex(view.indexAt(x,y), ListView.Center)
            }

            Rectangle {
                id: content
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                width: dragArea.width
                height: 70

                border.color: "#282930"
                border.width: 3

                color: dragArea.held ? "#6e7173" : "#434343"
                Behavior on color { ColorAnimation { duration: 100 } }

                radius: 2

                Drag.active: dragArea.held
                Drag.source: dragArea
                Drag.hotSpot.x: width / 2
                Drag.hotSpot.y: height / 2

                states: State {
                    when: dragArea.held

                    ParentChange {
                        target: content
                        parent: root
                    }
                    AnchorChanges {
                        target: content
                        anchors {
                            horizontalCenter: undefined
                            verticalCenter: undefined
                        }
                    }
                }

                Item{
                    id: songInfo
                    anchors.fill: parent
                    anchors.margins: 2

                    RowLayout{
                        anchors.fill: parent

                        Image{
                                source: "image://coverArt/" + dragArea.album + "/" + dragArea.albumArtists.join('%')
                                sourceSize.height: 55
                                sourceSize.width: 55
                                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                                Layout.preferredWidth: 55
                                Layout.preferredHeight: 55
                                Layout.leftMargin: 5
                            }

                        Item{
                            id: infoContainer
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            ColumnLayout{
                                anchors.fill: parent
                                anchors.leftMargin: 10
                                spacing: 0

                                Text{
                                    text: dragArea.title
                                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                                    Layout.preferredWidth: infoContainer.width - 10
                                    elide: Text.ElideRight
                                    color: "white"
                                    font.bold: true
                                }

                                Text{
                                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                                    Layout.preferredWidth: infoContainer.width - 10
                                    elide: Text.ElideRight
                                    text: dragArea.features.length === 0 ? dragArea.artist  : dragArea.artist + " feat. " + dragArea.features.join(", ")

                                }
                            }
                        }
                    }
                }
            }
            DropArea {
                anchors {
                    fill: parent
                    margins: 10
                }

                onEntered: (drag) => {
                    let src_index = drag.source.DelegateModel.itemsIndex
                    let target_index = dragArea.DelegateModel.itemsIndex
                    visualModel.items.move(src_index, target_index)

                    GlobalSingleton.playbackManager.nowPlaying.moveSong(src_index, target_index)



                }
            }
        }
    }
    DelegateModel {
        id: visualModel

        model: GlobalSingleton.playbackManager.nowPlaying.queueModel
        delegate: dragDelegate

    }

    ListView {
        id: view

        anchors {
            top: clearBtn.bottom
            left:parent.left
            right: parent.right
            rightMargin: 5
            bottom: parent.bottom
            bottomMargin: 5
            topMargin: 10
        }

        model: visualModel


        spacing: 4
        clip: true

        ScrollBar.vertical: ScrollBar {
            id:viewScrollBar
            policy: ScrollBar.AlwaysOn

            width: 10

            contentItem: Rectangle {
                implicitWidth: 10
                radius: 3
                color: "#2e2e2e"
            }

            background: Rectangle {
                implicitWidth: 10
                color: "#7a7a7a"
                radius: 3
            }
        }
    }
}
