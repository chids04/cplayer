pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts


import "../components"

Rectangle {
    id: songRect
    //width: songsListView.width-23
    radius: 10
    //color: index % 2 == 0 ? "#1e1f20" : "#131314"

    property string songDelegateLeadingArtist
    property var songObj
    property list<string> songFeatures
    property bool isContextMenuOpen: false
    property bool isHovered: false

    property alias songDelegateColor: songRect.color
    property alias songDelegateWidth: songRect.width
    property alias songDelegateHeight: songRect.height

    property alias songDelegateTitle: songTitle.text
    property alias songDelegateAuthors: songAuthors.text
    property alias songDelegateAlbum: songAlbum.text


    signal songDelegateClicked()
    signal songDelegateDoubleClicked()

    border.color: "#343434"

    Behavior on scale{
        NumberAnimation{
            duration: 200
        }
    }


    Rectangle{
        id: tintOverlay
        anchors.fill: parent
        radius: songRect.radius
        color: "#383838"
        opacity: 0

        Behavior on opacity{
            NumberAnimation {
                duration: 200
            }
        }
    }



    MouseArea {
        id: songClick
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onEntered: {
            songRect.scale = 1.05
            songRect.isHovered = true
            tintOverlay.opacity = 1
        }

        onExited: {
            if(!songRect.isContextMenuOpen){
                songRect.isHovered = false
                tintOverlay.opacity = 0
                songRect.scale = 1
            }

        }

        onDoubleClicked: {
            songRect.state = 'doubleClicked'
            songRect.songDelegateDoubleClicked()
        }

        onReleased: {
            songRect.state = ''
        }

        onClicked: mouse => {
            if(mouse.button === Qt.LeftButton){
                songRect.songDelegateClicked()
            }
            else if(mouse.button === Qt.RightButton){
                songRect.isContextMenuOpen = true
                tintOverlay.opacity = 1
                contextMenu.openContextMenu(songRect.songObj)
            }


        }

        SongContextMenu{
            id:contextMenu
            onClosed: {
                songRect.isContextMenuOpen = false
                tintOverlay.opacity = 0

            }
        }


        Behavior on scale {
            NumberAnimation {
                duration: 200
                easing.type: Easing.OutBack
            }
        }
    }

    states: [
            State {
                name: "doubleClicked"
                PropertyChanges {
                    songRect{
                        scale: 0.95
                    }
                }
            }
        ]

    transitions: [
            Transition {
                from: ""
                to: "doubleClicked"
                reversible: true
                NumberAnimation {
                    target: songRect
                    property: "scale"
                    duration: 200
                    easing.type: Easing.OutBack
                }
            }
        ]

    RowLayout {

        anchors{
            fill: parent
        }
        spacing:5


        Image {
            id: albumImage
            source: "image://coverArt/" + songRect.songDelegateAlbum + "/" + songRect.songFeatures.join('%')
            sourceSize.width: 30
            sourceSize.height: 30
            Layout.rightMargin: 10
            Layout.leftMargin: 10
        }

        ColumnLayout{
            Text {
                id:songTitle
                font.bold: true
                font.pointSize: 16
                Layout.fillWidth: true
                elide: Text.ElideRight
                Layout.rightMargin: 3
                color: "white"
            }

            Text {
                id: songAuthors
                color: "white"
                elide: Text.ElideRight
                Layout.rightMargin: 3
                Layout.fillWidth: true
            }

            Text {
                id: songAlbum
                //text: album
                color: "white"
                Layout.fillWidth: true
                Layout.rightMargin: 3
                elide: Text.ElideRight

            }
        }

    //     Item {
    //         Layout.preferredWidth: parent.width * 0.33
    //         Layout.preferredHeight: parent.height

    //         RowLayout{
    //             anchors.fill: parent
    //             spacing: 0

    //             Text{
    //                 id: songNumber
    //                 Layout.preferredWidth: 40
    //                 Layout.maximumWidth: 40
    //                 elide: Text.ElideRight
    //                 Layout.leftMargin: 10
    //                 horizontalAlignment: Text.AlignHCenter
    //                 color: "white"
    //             }

    //             Image {
    //                 id: albumImage
    //                 Layout.preferredWidth:60
    //                 Layout.preferredHeight:60
    //                 source: "image://coverArt/" + songDelegateAlbum + "/" + songFeatures.join('%')
    //                 sourceSize.width: 60
    //                 sourceSize.height: 60
    //                 Layout.rightMargin: 10
    //                 Layout.leftMargin: 10
    //             }

    //             Text {
    //                 id:songTitle
    //                 font.bold: true
    //                 color: "white"
    //                 Layout.fillWidth: true
    //                 elide: Text.ElideRight
    //             }




    //         }


    //     }

    //     Item{
    //         Layout.preferredWidth: parent.width * 0.33
    //         Layout.preferredHeight: parent.height


    //         Text {
    //             id: songAuthors
    //             color: "white"
    //             width: parent.width
    //             height: parent.height
    //             elide: Text.ElideRight
    //             horizontalAlignment: Text.AlignHCenter
    //             verticalAlignment: Text.AlignVCenter
    //         }
    //     }



    //     Item{
    //         Layout.preferredWidth: parent.width * 0.33
    //         Layout.preferredHeight: parent.height

    //         Text {
    //             id: songAlbum
    //             //text: album
    //             color: "white"
    //             width:parent.width
    //             height: parent.height
    //             horizontalAlignment: Text.AlignHCenter
    //             verticalAlignment: Text.AlignVCenter
    //             elide: Text.ElideRight

    //         }
    //     }


    // }

    }
}


