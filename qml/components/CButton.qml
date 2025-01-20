pragma ComponentBehavior: Bound

import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Controls.Material 2.15

RoundButton {
    id: customButton

    width: textMetrics.width + 2 * customButton.padding
    height: textMetrics.height + 2 * customButton.padding

    radius: 20
    padding:20

    property alias buttonText: contentText.text
    property alias buttonTextSize: contentText.font.pointSize
    property alias buttonColor: contentBackground.color

    signal buttonClicked();

    onClicked: {
        buttonClicked();
    }

    contentItem: Text{
        id: contentText
        text: "ButtonText"
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 12
        color: "white"
    }

    TextMetrics {
            id: textMetrics
            text: contentText.text
            font: contentText.font
    }


    property color borderColor: "#2f3137"
    Behavior on borderColor {
        PropertyAnimation{
            duration: 300
        }
    }

    hoverEnabled: true
    onHoveredChanged: {
        borderColor = hovered ? "#606060" : "#2f3137"
    }

    background: Rectangle {
        id: contentBackground
        color: "transparent"
        radius: customButton.radius
        border.color: customButton.borderColor
        border.width: 2
    }

    onPressedChanged: {
            if (customButton.pressed) {
                // Scale down when pressed
                customButton.scale = 0.95
            } else {
                // Scale back to normal when released
                customButton.scale = 1.0
            }
        }

        // Smooth scale transition
        Behavior on scale {
            NumberAnimation {
                duration: 200
                easing.type: Easing.OutBack
            }
        }

}
