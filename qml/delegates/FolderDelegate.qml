pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls

import "../components"

Item {
    id: folderDelegate
    property string folderDelegateName
    property string folderDelegatePath
    property int folderIndex
    property alias delegateWidth: folderDelegate.width

    height: 50


    Rectangle{
        anchors.fill: parent
        color: "#1e1e20"
        radius: 5


        RowLayout{
            anchors.fill: parent
            anchors.leftMargin: 5

            ColumnLayout{
                Layout.alignment: Qt.AlignLeft | Qt.AlignHCenter
                spacing: 0

                Text{
                    id: folderNameText
                    text: folderDelegate.folderDelegateName
                    color: "white"
                    font.bold: true
                    font.pointSize: 10

                }

                Text{
                    id:folderPathText
                    text: folderDelegate.folderDelegatePath
                    color: "white"
                    font.pointSize: 10

                }
            }

            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Image{
                id: removeBtn
                Layout.alignment: Qt.AlignRight | Qt.AlignHCenter
                source: "qrc:/resource/ui/assets/x.png"
                sourceSize.height: 30
                sourceSize.width: 30
                visible: false

                //visible: false
                MouseArea{
                    id: removeBtnMA
                    anchors.fill: parent
                    hoverEnabled: true
                    //propagateComposedEvents: true
                    onEntered: removeBtn.opacity = 0.5
                    onExited: removeBtn.opacity = 1
                    onClicked: confirmPopup.openFolderPopup(folderDelegate.folderIndex, folderDelegate.folderDelegatePath)

                    onPressedChanged: {
                        if(pressed){
                            removeBtn.scale = 0.7
                        }
                        else{
                            removeBtn.scale = 1
                        }
                    }

                    ToolTip.visible: removeBtnMA.containsMouse
                    ToolTip.text: "fuk"
                }

                Behavior on opacity{
                    NumberAnimation{
                        duration: 100
                    }
                }

                Behavior on scale{
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }

            }
        }
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        onEntered: removeBtn.visible = true
        onExited: removeBtn.visible = false
    }

    FolderDelPopUp{
        id: confirmPopup
    }




}
