pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

import cplayer


Item {
    id: albumCard

    property alias itemWidth : albumCard.width
    property alias itemHeight: albumCard.height

    required property string albumName
    required property var albumObjRole
    required property list<string> albumArtists

    property bool pressed: false

    Behavior on scale {
        NumberAnimation {
            duration: 200
            easing.type: Easing.OutBack
        }
    }

    scale: pressed ? 0.95 : 1

    Rectangle {
        id: overlay
        anchors.fill: parent
        color : "#0b0b0b"
        radius: 10
        opacity : 0

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: overlay.opacity = 1
        onExited: overlay.opacity = 0

        onPressed: {
            albumCard.pressed = true
            GlobalSingleton.songManager.setAlbum(albumCard.albumObjRole)
            GlobalSingleton.viewController.selectAlbum()
        }
        onReleased: albumCard.pressed = false

        // onClicked: {
        //     GlobalSingleton.songManager.setAlbum(albumCard.albumObjRole)
        //     GlobalSingleton.viewController.selectAlbum()
        // }
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        anchors.bottomMargin: 5

        Image {
            id: albumImage
            source: "image://coverArt/" + albumCard.albumName + "/" + albumCard.albumArtists.join("++?")
            sourceSize.width: 200
            sourceSize.height: 200

            Layout.preferredHeight: albumCard.width - 80
            Layout.preferredWidth: albumCard.width - 80
            Layout.alignment: Qt.AlignHCenter
            asynchronous: true
        }

        Text {
            text: albumCard.albumName
            font.bold: true
            font.pointSize: 16
            Layout.leftMargin: 5
            Layout.rightMargin: 5
            color: "white"
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }

        Text {
            text: albumCard.albumArtists.join(", ")
            color: "white"
            Layout.alignment: Qt.AlignHCenter
            Layout.leftMargin: 5
            Layout.rightMargin: 5
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }
    }
}
