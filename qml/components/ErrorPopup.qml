import QtQuick
import QtQuick.Layouts
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

    // Pop-up content
    // background: Rectangle {
    //     id: errorPopUpDelegate
    //     width: textMetrics.width
    //     height: textMetrics.height
    //     anchors.fill: parent
    //     color: "#202020"
    //     radius: 20
    //     border.color: "#2f3137"
    //     border.width: 2

    //     Text{
    //         id: message
    //         anchors.centerIn: parent
    //         text: errorText
    //         font.pointSize: 14
    //         color: "white"

    //         onTextChanged: {
    //             console.log(textMetrics.width)
    //             console.log("text changed")
    //             textMetrics.text = message.text
    //             errorPopUpDelegate.width = textMetrics.width
    //             console.log(errorPopUpDelegate.width)
    //             console.log(textMetrics.width)
    //         }
    //     }

    //     TextMetrics{
    //         id: textMetrics
    //         font: message.font
    //         text: message.text
    //     }

    // }

    contentItem: Text{
        text: "<b><u>Error:</u></b> " + errorText
        font.pointSize: 14
        color: "white"
    }



}
