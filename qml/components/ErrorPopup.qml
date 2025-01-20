import QtQuick
import QtQuick.Controls

// ErrorPopup.qml

Popup {
    id: popup
    //width: errorPopUpDelegate.width + 20
    //height: errorPopUpDelegate.height + 20
    modal: true
    focus: true

    anchors.centerIn: Overlay.overlay
    dim: true

    property string errorText

    function openPopup(text){
        errorText = text
        popup.open()
    }

    Timer{
        id: autoClose
        interval: 2000
        running: popup.visible
        onTriggered: popup.close()
    }

    enter: Transition {
                ParallelAnimation {
                    id: popIn
                    PropertyAnimation {
                        target: popup
                        property: "scale"
                        from: 0.9
                        to: 1
                        duration: 50
                    }
                    PropertyAnimation {
                        target: popup
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
                        target: popup
                        property: "scale"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                    PropertyAnimation {
                        target: popup
                        property: "opacity"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                }
            }

        background: Rectangle{
            anchors.fill: parent
            color: "#202020"
            border.color: "#2f3137"
            border.width: 2
            radius: 20
        }

    contentItem: Text{
        text: "<b><u>Error:</u></b> " + popup.errorText
        font.pointSize: 14
        color: "white"
    }



}
