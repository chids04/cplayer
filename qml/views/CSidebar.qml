pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

Item {
    id: sideBar

    property Item sidebarStackView;

    Layout.preferredWidth: 80
    Layout.fillHeight: true
    state: 'close'

    states: [
        State {
            name: 'open'

            PropertyChanges {
                sideBar {
                    Layout.preferredWidth: 270
                }
            }

            PropertyChanges {
                timer {
                    index: 0
                }
            }
        },
        State {
            name: 'close'

            PropertyChanges {
                sideBar {
                    Layout.preferredWidth: 80
                }
            }

            PropertyChanges {
                timer {
                    index: 0
                }
            }
        }
    ]

    transitions: [
        Transition {
            from: 'close'
            to: 'open'

            // NumberAnimation {
            //     properties: 'Layout.preferredWidth'
            //     duration: 0
            //     easing.type: Easing.OutCubic
            // }

            ScriptAction {
                script: {
                    timer.start();
                }
            }
        },
        Transition {
            from: 'open'
            to: 'close'

            SequentialAnimation {

                ScriptAction {
                    script: {
                        timer.start();
                    }
                }

                // PauseAnimation {
                //     duration: 600
                // }

                // NumberAnimation {
                //     properties: 'Layout.preferredWidth'
                //     duration: 0
                //     easing.type: Easing.OutCubic
                // }
            }
        }
    ]

    Timer {
        id: timer

        property int index: 0

        interval: 0

        onTriggered: {
            if (sideBar.state == 'open')
                columnItems.itemAt(index).state = 'left';
            else
                columnItems.itemAt(index).state = 'middle';

            if (++index != columnItems.model.length)
                timer.start();
        }
    }

    Rectangle {
        id: body

        topRightRadius: 10
        bottomRightRadius: 10

        color: '#222222'
        anchors.fill: parent

        ColumnLayout {
            id: layout
            width: parent.width
            height: parent.height
            spacing: 0

            //extra item here not needed,

            Item {
                Layout.topMargin: 15
                Layout.fillWidth: true
                Layout.preferredHeight: 80

                Item{
                    id: menuContainer
                    width: 50
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter


                    Behavior on scale {
                        NumberAnimation{
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    }
                    Rectangle {
                        id: menuButton
                        color: '#1d1d1d'

                        anchors.fill: parent
                        radius: 10
                        opacity: 0

                        Behavior on opacity {
                            NumberAnimation{
                                duration: 300
                                easing.type: Easing.InOutQuad
                            }
                        }


                        // Behavior on color {
                        //     ColorAnimation { duration: 200 }
                        // }

                        MouseArea {
                            id: menuMouseArea
                            anchors.fill: parent
                            hoverEnabled: true

                            onPressed: menuContainer.scale = 0.9
                            onReleased: menuContainer.scale = 1

                            onClicked: {
                                if (sideBar.state == 'close'){
                                    sideBar.state = 'open'
                                    menuButton.opacity = 1
                                }
                                else{
                                    sideBar.state = 'close';
                                    menuButton.opacity = 0
                                }
                            }
                        }

                    }

                    Image {
                        source: "qrc:/resource/ui/assets/Menu.svg"
                        sourceSize: Qt.size(30, 30)
                        anchors.centerIn: parent
                        opacity: 1
                    }
                }


            }

            // Scrollable Buttons
            Flickable {
                id: flickable
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                contentHeight: buttonColumn.implicitHeight
                flickableDirection: Flickable.VerticalFlick

                ColumnLayout {
                    id: buttonColumn
                    width: parent.width
                    spacing: 20

                    Repeater {
                        id: columnItems
                        model: [{buttonText: 'home', fileName: 'Home.svg', qmlPath: "HomePage.qml"},
                            {buttonText: 'songs', fileName: "Song.svg", qmlPath: "Songs.qml"},
                            {buttonText: 'albums', fileName: "Album.svg", qmlPath: "Albums.qml"},
                            {buttonText: 'playlists', fileName: "Playlist.svg", qmlPath: "Playlists.qml"},
                            {buttonText: 'settings', fileName: "Settings.svg", qmlPath: "Settings.qml"}]

                        delegate: Rectangle {
                            id: button

                            required property var model
                            required property var modelData


                            Layout.preferredWidth: 50
                            Layout.preferredHeight: 50
                            radius: 10
                            //color: buttonMouseArea.containsMouse ? '#404142' : 'transparent'
                            color: "transparent"
                            Layout.alignment: Qt.AlignLeft
                            state: 'middle'

                            Rectangle{
                                id: background
                                anchors.fill: parent
                                radius: 10
                                color: '#1d1d1d'
                            }

                            // Behavior on color {
                            //     ColorAnimation {
                            //         duration: 200
                            //     }
                            // }

                            states: [
                                State {
                                    name: 'left'

                                    PropertyChanges {
                                        button {
                                            Layout.leftMargin: 10
                                            Layout.preferredWidth: 240
                                        }

                                    }

                                    PropertyChanges{
                                        background{
                                            opacity: 0
                                        }
                                    }

                                    PropertyChanges {
                                        title {
                                            opacity: 1
                                        }
                                    }
                                },
                                State {
                                    name: 'middle'

                                    PropertyChanges {
                                        button {
                                            Layout.leftMargin: Math.ceil((sideBar.width - 50) / 2)
                                            Layout.preferredWidth: 50
                                        }
                                    }

                                    PropertyChanges {
                                        title {
                                            opacity: 0
                                        }
                                    }

                                    PropertyChanges {
                                        background{
                                            opacity: 1
                                        }
                                    }
                                }
                            ]

                            transitions: [
                                Transition {
                                    from: 'middle'
                                    to: 'left'

                                    // NumberAnimation {
                                    //     properties: 'Layout.leftMargin, Layout.preferredWidth, opacity'
                                    //     duration: 300
                                    //     easing.type: Easing.InOutSine
                                    // }
                                },
                                Transition {
                                    from: 'left'
                                    to: 'middle'

                                    // NumberAnimation {
                                    //     properties: 'Layout.leftMargin, Layout.preferredWidth'
                                    //     duration: 300
                                    //     easing.type: Easing.InOutSine
                                    // }
                                }
                            ]

                            MouseArea {
                                id: buttonMouseArea

                                hoverEnabled: true
                                anchors.fill: parent

                                onEntered: {
                                    if(button.state == "left"){
                                        background.opacity = 1
                                    }
                                }

                                onExited: {
                                    if(button.state == "left"){
                                        background.opacity = 0
                                    }
                                }

                                onClicked:{
                                    sideBar.sidebarStackView.push(button.modelData.qmlPath)
                                }
                            }

                            Image {
                                source: "qrc:/resource/ui/assets/" + button.modelData.fileName
                                sourceSize: Qt.size(30, 30)
                                anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                            }

                            Text {
                                id: title
                                text: button.modelData.buttonText
                                font.pointSize: 20
                                color: "white"
                                anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 55 }
                            }
                        }
                    }
                }
            }
        }
    }
}
