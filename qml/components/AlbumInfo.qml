pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic

Popup {
    id: popUp
    width: 660
    height: 500
    modal: true
    focus: true
    dim: true
    parent: Overlay.overlay
    padding: 8

    signal albumSelected(Album album)

    anchors.centerIn: parent
    
    function openPopup(){
        popUp.open()
    }

    enter: Transition {
        ParallelAnimation {
            id: popIn
            PropertyAnimation {
                target: popUp
                property: "scale"
                from: 0.9
                to: 1
                duration: 50
            }
            PropertyAnimation {
                target: popUp
                property: "opacity"
                from: 0.9
                to: 1
                duration: 50
            }
        }
    }
    exit: Transition {
        ParallelAnimation {
            id: popOut
            PropertyAnimation {
                target: popUp
                property: "scale"
                from: 1
                to: 0.9
                duration: 50
            }
            PropertyAnimation {
                target: popUp
                property: "opacity"
                from: 1
                to: 0.9
                duration: 50
            }
        }
    }

    background: Rectangle {
        id: popUpDelegate
        anchors.fill: parent
        color: "#202020"
        radius: 5

        border.color: "#424345"
        border.width: 5
    }

    contentItem: Item {
        ColumnLayout{
            anchors.fill: parent

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

        ListView{
            id: listview
            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true
            spacing: 5

            model: GlobalSingleton.songManager.albumSearchModel
            
            ScrollBar.vertical: ScrollBar {
                id:albumScrollBar
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
            delegate: Rectangle{
                id: albumDelegate
                width: listview.width
                height: 80
                required property string albumName
                required property list<string> albumArtists;
                required property Album albumObjRole

                color: "#262729"

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        popUp.albumSelected(albumDelegate.albumObjRole)
                        popUp.close()
                    }
                }

                RowLayout{
                    
                    anchors{
                        left: parent.left
                        top: parent.top
                        bottom: parent.bottom
                    }
                    Image{
                        id: albumImage
                        source: "image://coverArt/" + albumDelegate.albumName + "/" + albumDelegate.albumArtists.join("++?")
                        sourceSize.width: 100
                        sourceSize.height: 100

                        Layout.preferredHeight: 60
                        Layout.preferredWidth: 60
                        Layout.alignment: Qt.AlignLeft
                        Layout.leftMargin: 5
                        asynchronous: true
                    }

                    ColumnLayout{
                        Layout.alignment: Qt.AlignVCenter
                        Layout.leftMargin: 5
                        Layout.fillWidth: true

                        Text{
                            text: albumDelegate.albumName
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                            color: "white"
                        }


                        Text{
                            text: albumDelegate.albumArtists.join(", ")
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                            color: "white"
                        }
                    }
                }
            }
        }

    }
    }

}