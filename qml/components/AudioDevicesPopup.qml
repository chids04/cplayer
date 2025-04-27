pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls.Basic

import cplayer

Popup{
    id: popup
    width: 300
    height: 200
    padding: 0


    parent: Overlay.overlay
    x: parent.width - popup.width - 30
    y: parent.height - popup.height - 100
    background: Item{

    }

    function openPopup(){
        popup.open()
    }

    contentItem: Rectangle{

        id: audioDevices
        width: 200
        height: 100

        color: "#202020"
        border.color: "#424345"
        border.width: 2
        radius: 5

        Text{
            id: selectAudioText
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: parent.horizontalCenter
            text: "outputs"
            font.bold: true
            font.pointSize: 14
            color: "white"
        }

        Rectangle{
            id: seperator
            height: 1
            border.color: "grey"
            border.width: 1
            anchors.top: selectAudioText.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.topMargin: 10
            anchors.bottomMargin: 10
            anchors.leftMargin: 10
            anchors.rightMargin: 10
        }

        ListView {
            id: audioDeviceList
            anchors.top: seperator.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.topMargin: 10

            model: GlobalSingleton.playbackManager.mediaPlayer.audioDeviceModel
            clip: true

            ScrollBar.vertical: ScrollBar {
                id:optionScrollbar
                policy: ScrollBar.AlwaysOn

                width: 10

                contentItem: Rectangle {
                    implicitWidth: 10
                    radius: 3
                    color: "#2e2e2e"
                }

                background: Rectangle {
                    implicitWidth: 10
                    color: "grey"
                    radius: 3
                }
            }

            delegate: Rectangle {
                id: deviceDelegate
                width: audioDeviceList.width - 14
                height: 40
                radius: 5

                required property string deviceName
                required property int index
                required property bool isSelected

                color: isSelected ? "#343434" : "transparent"

                Text{
                    text: deviceDelegate.deviceName
                    color: "white"
                    width: deviceDelegate.width
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 10
                    anchors.verticalCenter: parent.verticalCenter
                }


                MouseArea{
                    anchors.fill: parent
                    onClicked: GlobalSingleton.playbackManager.mediaPlayer.audioDeviceModel.selectDevice(deviceDelegate.index)

                    onPressedChanged: {
                        if(pressed){
                            deviceDelegate.scale = 0.95
                        }
                        else{
                            deviceDelegate.scale = 1
                        }
                    }

                }

                Behavior on scale {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
}
