import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import QtQuick.Controls.Basic
import com.c.MediaController
import com.c.ViewController


Item{
    Layout.fillHeight: true
    Layout.preferredWidth: 250

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
            spacing: 30
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 20
            anchors.topMargin: 20

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

                    Image{
                        id: songViewIcon
                        source: "qrc:/resource/ui/assets/musicIcon.png"
                        Layout.alignment: Qt.AlignVCenter
                    }

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
                            text: qsTr("Songs")
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        songsWindow.color = "#1d1d1e"
                    }

                    onExited: {
                        songsWindow.color = "transparent"
                    }

                    onClicked: {
                        ViewController.songView()
                    }

                }
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

                    Image{
                        id: albumViewIcon
                        source: "qrc:/resource/ui/assets/albumIcon.png"
                        Layout.alignment: Qt.AlignVCenter
                    }

                    Rectangle {
                        height: albumText.height
                        Layout.fillWidth: true
                        color: "transparent"
                        Layout.alignment: Qt.AlignVCenter

                        Text {
                            id: albumText
                            color: "white"
                            font.pointSize: 30
                            text: qsTr("Albums")
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        albumWindow.color = "#1d1d1e"
                    }

                    onExited: {
                        albumWindow.color = "transparent"
                    }

                    onClicked: {
                        ViewController.albumView()
                    }

                }
            }

            Rectangle{
                id: foldersWindow
                Layout.fillWidth: true
                height: 60
                color: "transparent"
                bottomRightRadius: 40
                topRightRadius: 40

                RowLayout{
                    anchors.leftMargin: 10
                    anchors.fill: parent
                    spacing: 10

                    Image{
                        id: foldersViewIcon
                        source: "qrc:/resource/ui/assets/folderIcon.png"
                        Layout.alignment: Qt.AlignVCenter
                    }

                    Rectangle {
                        height: foldersText.height
                        Layout.fillWidth: true
                        color: "transparent"
                        Layout.alignment: Qt.AlignVCenter

                        Text {
                            id: foldersText
                            color: "white"
                            font.pointSize: 30
                            text: qsTr("Folders")
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        foldersWindow.color = "#1d1d1e"
                    }

                    onExited: {
                        foldersWindow.color = "transparent"
                    }

                    onClicked: {
                        ViewController.foldersView()
                    }

                }
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

                    Image{
                        id: playlistsIcon
                        source: "qrc:/resource/ui/assets/folderIcon.png"
                        Layout.alignment: Qt.AlignVCenter
                    }

                    Rectangle {
                        height: playlistsText.height
                        Layout.fillWidth: true
                        color: "transparent"
                        Layout.alignment: Qt.AlignVCenter

                        Text {
                            id: playlistsText
                            color: "white"
                            font.pointSize: 30
                            text: qsTr("Playlists")
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        playlistsWindow.color = "#1d1d1e"
                    }

                    onExited: {
                        playlistsWindow.color = "transparent"
                    }

                    onClicked: {
                        ViewController.playlistsView()
                    }

                }
            }
        }
    }
}




