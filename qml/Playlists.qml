import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Dialogs
import QtQuick.Controls.Basic

import com.c.MusicLibrary
import com.c.FolderView
import com.c.FolderModel

import "./components"


Item {
    id: playlistsView
    anchors.fill: parent

    ColumnLayout{
        anchors.fill: parent

        RowLayout{
            Layout.fillWidth: true
            spacing: 20

            Text{
                text: "Playlists"
                font.bold: true
                font.pointSize: 100
                color: "white"
                Layout.preferredWidth: width
            }

            CButton{
                id: addPlaylistButton
                buttonText: "Add Playlist"
                buttonTextSize: 24
                Layout.preferredWidth: width

                onButtonClicked: {
                    popUp.open()
                }

            }

            Popup {
                id: popUp
                width: 300
                height: 200
                modal: true
                focus: true

                anchors.centerIn: Overlay.overlay


                // Pop-up content
                background: Rectangle {
                    id: popUpDelegate
                    anchors.fill: parent
                    color: "#202020"

                    border.color: "#2f3137"
                    border.width: 2

                    // Input field for user information
                    TextField {
                        id: inputField
                        width: 250
                        anchors.centerIn: parent
                        placeholderText: "Enter Playlist Name"
                        placeholderTextColor: "#6a6f76"
                        color: "white"

                        background: Rectangle{
                            color: "#2f3137"
                            radius: 10

                        }

                        TextMetrics{
                            id: metrics
                            elideWidth: inputField.width
                        }

                    }
                }

                // Blurring the main window when the pop-up is open
                onOpened: {
                    mainWindow.opacity = 0.5
                }
                onClosed: {
                    mainWindow.opacity = 1
                }
            }

        }

        Item{
            Layout.fillHeight: true
        }
    }

}
