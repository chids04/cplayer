import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import QtQuick.Controls.Basic

//import com.c.ViewController

import cplayer

Item{
    id: sidebarItem
    Layout.fillHeight: true
    Layout.preferredWidth: 250

    property int selectedItem: -1

    MultiEffect{
        source: sidebarNav
        anchors.fill: sidebarNav
        shadowBlur: 0.7
        shadowEnabled: true
        shadowColor: "#80000000"
        shadowHorizontalOffset: 10
        autoPaddingEnabled: true
    }

    Rectangle{
        id: sidebarNav
        anchors.fill: parent
        color: "#232425"
        topRightRadius: 20

        ColumnLayout{
            spacing: 10
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 20


            Rectangle{
                id: settingsPanel
                color: "#424445"
                height: 40
                width: 50
                bottomLeftRadius: 10
                bottomRightRadius: 10
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                Image{
                    id: settingsCog
                    anchors.centerIn: parent
                    source: "qrc:/resource/ui/assets/settingsCog.png"
                    sourceSize.height: 30
                    sourceSize.width: 30

                    Behavior on opacity{
                        NumberAnimation {
                            duration: 100
                        }
                    }

                    Behavior on scale{
                        NumberAnimation {
                            duration: 200
                            easing.type: Easing.InOutQuad
                        }
                    }

                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            songsWindow.state = ""
                            albumWindow.state = ""
                            playlistsWindow.state = ""

                            ViewController.settingsView()


                        }

                        onEntered: {
                            settingsCog.opacity = 0.5
                        }

                        onExited: {
                            settingsCog.opacity = 1
                        }

                        onPressedChanged: {
                            if(pressed){
                                settingsCog.scale = 0.7
                            }
                            else{
                                settingsCog.scale = 1
                            }
                        }

                    }
                }
            }

            Rectangle{
                id: songsWindow
                Layout.fillWidth: true
                height: 60
                color: "transparent"

                bottomRightRadius: 40
                topRightRadius: 40

                RowLayout{
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    spacing: 10


                    Rectangle {
                        height: songText.height
                        width: songText.width
                        Layout.fillWidth: true
                        color: "transparent"
                        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                        Text {
                            id: songText
                            color: "white"
                            font.pointSize: 30
                            text: qsTr("songs")
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        if(songsWindow.state !== "clicked") songsWindow.color = "#1d1d1e"
                    }

                    onExited: {
                        if(songsWindow.state !== "clicked") songsWindow.color = "transparent"
                    }

                    onClicked: {
                        songsWindow.state = "clicked"
                        albumWindow.state = ""
                        playlistsWindow.state = ""

                        ViewController.songView()
                    }
                }

                states: [
                    State {
                        name: "clicked"
                        PropertyChanges {
                            target: songsWindow;
                            color: "#1d1d1e"
                        }
                    },

                    State{
                        name: ""
                        PropertyChanges {
                            target: songsWindow;
                            color: "transparent"

                        }
                    }

                ]
            }

            Rectangle{
                id: albumWindow
                Layout.fillWidth: true
                height: 60
                color: "transparent"
                bottomRightRadius: 40
                topRightRadius: 40

                RowLayout{
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    spacing: 10



                    Rectangle {
                        height: albumText.height
                        Layout.fillWidth: true
                        color: "transparent"
                        Layout.alignment: Qt.AlignVCenter

                        Text {
                            id: albumText
                            color: "white"
                            font.pointSize: 30
                            text: qsTr("albums")
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        if(albumWindow.state != "clicked") albumWindow.color = "#1d1d1e"
                    }

                    onExited: {
                        if(albumWindow.state != "clicked") albumWindow.color = "transparent"
                    }

                    onClicked: {
                        albumWindow.state = "clicked"
                        songsWindow.state = ""
                        playlistsWindow.state = ""
                        selectedItem = 1
                        ViewController.albumView()
                    }

                }

                states: [
                    State {
                        name: "clicked"

                        PropertyChanges {
                            target: albumWindow;
                            color: "#1d1d1e"
                        }
                    },

                    State{
                        name: ""
                        PropertyChanges {
                            target: albumWindow;
                            color: "transparent"

                        }
                    }

                ]
            }



            Rectangle{
                id: playlistsWindow
                Layout.fillWidth: true
                height: 60
                color: "transparent"
                bottomRightRadius: 40
                topRightRadius: 40

                RowLayout{
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    spacing: 10


                    Rectangle {
                        height: playlistsText.height
                        Layout.fillWidth: true
                        color: "transparent"
                        Layout.alignment: Qt.AlignVCenter

                        Text {
                            id: playlistsText
                            color: "white"
                            font.pointSize: 30
                            text: qsTr("playlists")
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        if(playlistsWindow.state != "clicked") playlistsWindow.color = "#1d1d1e"
                    }

                    onExited: {
                        if(playlistsWindow.state != "clicked") playlistsWindow.color = "transparent"
                    }

                    onClicked: {
                        playlistsWindow.state = "clicked"
                        albumWindow.state = ""
                        songsWindow.state = ""
                        ViewController.playlistsView()
                    }

                }

                states: [
                    State {
                        name: "clicked"

                        PropertyChanges {
                            target: playlistsWindow;
                            color: "#1d1d1e"
                        }
                    },

                    State{
                        name: ""
                        PropertyChanges {
                            target: playlistsWindow;
                            color: "transparent"

                        }
                    }

                ]
            }
        }
    }
}




