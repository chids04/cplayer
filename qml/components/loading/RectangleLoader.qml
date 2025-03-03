pragma ComponentBehavior: Bound
import QtQuick 2.7

Item {

    // ----- Public Properties ----- //

    property alias barCount: repeater.model
    property color color: "white"
    property int spacing: 5

    property bool running: true

    id: root
    onRunningChanged: {
        if (barCount !== repeater.count || timer._barIndex <= barCount - 1) {
            return;
        }

        for (var barIndex = 0; barIndex < barCount; barIndex++) {
            if (running) {
                if (repeater.itemAt(barIndex)) {
                    repeater.itemAt(barIndex).playAnim();
                }
            }
            else {
                if (repeater.itemAt(barIndex)) {
                    repeater.itemAt(barIndex).pauseAnim();
                }
            }
        }
    }

    Repeater {
        id: repeater
        delegate: Component {
            Rectangle {
                id: pulseDelegate
                required property int index

                property var playAnim: playAnimation
                property var pauseAnim: pauseAnimation

                width: (root.width / root.barCount) - root.spacing
                height: root.height
                x: index * width + root.spacing * index
                transform: Scale {
                    id: rectScale
                    origin {
                        x: pulseDelegate.width / 2
                        y: pulseDelegate.height / 2
                    }
                }
                transformOrigin: Item.Center
                color: root.color

                SequentialAnimation {
                    id: anim
                    loops: Animation.Infinite

                    NumberAnimation { target: rectScale; property: "yScale"; from: 1; to: 1.5; duration: 300 }
                    NumberAnimation { target: rectScale; property: "yScale"; from: 1.5; to: 1; duration: 300 }
                    PauseAnimation { duration: root.barCount * 150 }
                }

                function playAnimation() {
                    if (anim.running == false) {
                        anim.running = true;
                    }

                    if (anim.paused) {
                        anim.paused = false;
                    }
                }

                function pauseAnimation() {
                    if (anim.running) {
                        anim.paused = true;
                    }
                }
            }
        }
    }

    Timer {
        // ----- Private Properties ----- //
        property int _barIndex: 0

        id: timer
        interval: 80
        repeat: true
        onTriggered: {
            if (_barIndex === root.barCount) {
                stop();
            }
            else {
                repeater.itemAt(_barIndex).playAnim();
                if (root.running === false) {
                    repeater.itemAt(_barIndex).pauseAnim();
                }

                _barIndex++;
            }
        }
        Component.onCompleted: start()
    }
}
