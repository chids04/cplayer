import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


Rectangle {
    id: songRect
    //width: songsListView.width-23
    radius: 10
    //color: index % 2 == 0 ? "#1e1f20" : "#131314"

    property string songDelegateLeadingArtist
    property int songDelegateIndex
    property bool songFromAlbum
    property var songObj
    property list<string> songFeatures
    property bool isContextMenuOpen: false

    property alias songDelegateColor: songRect.color
    property alias songDelegateWidth: songRect.width
    property alias songDelegateHeight: songRect.height

    property alias songDelegateNumber: songNumber.text
    property alias songDelegateTitle: songTitle.text
    property alias songDelegateAuthors: songAuthors.text
    property alias songDelegateAlbum: songAlbum.text


    signal songDelegateClicked()
    signal songDelegateDoubleClicked()


    Rectangle{
        id: tintOverlay
        anchors.fill: parent
        radius: songRect.radius
        color: "transparent"
    }



    MouseArea {
        id: songClick
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onEntered: {
            tintOverlay.color = "#383838"
        }

        onExited: {
            if(!songRect.isContextMenuOpen){
                tintOverlay.color = "transparent"
            }

        }

        onDoubleClicked: {
            songRect.state = 'doubleClicked'
            songDelegateDoubleClicked()
        }

        onReleased: {
            songRect.state = ''
        }

        onClicked: mouse => {
            if(mouse.button === Qt.LeftButton){
                songDelegateClicked()
            }
            else if(mouse.button === Qt.RightButton){
                isContextMenuOpen = true
                tintOverlay.color = "#383838"
                contextMenu.openContextMenu(songObj)
            }


        }

        SongContextMenu{
            id:contextMenu
            onClosed: {
                songRect.isContextMenuOpen = false
                tintOverlay.color = "transparent"
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
                    target: songRect
                    scale: 0.95
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

        Item {
            Layout.preferredWidth: parent.width * 0.33
            Layout.preferredHeight: parent.height

            RowLayout{
                anchors.fill: parent
                spacing: 0

                Text{
                    id: songNumber
                    Layout.preferredWidth: 40
                    Layout.maximumWidth: 40
                    elide: Text.ElideRight
                    Layout.leftMargin: 10
                    horizontalAlignment: Text.AlignHCenter
                    color: "white"
                }

                Image {
                    id: albumImage
                    width:60
                    height:60
                    source: "image://coverArt/" + songDelegateAlbum + "/" + songFeatures.join('%')
                    sourceSize.width: 60
                    sourceSize.height: 60
                    Layout.rightMargin: 10
                    Layout.leftMargin: 10
                }

                Text {
                    id:songTitle
                    font.bold: true
                    color: "white"
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }




            }


        }

        Item{
            Layout.preferredWidth: parent.width * 0.33
            Layout.preferredHeight: parent.height


            Text {
                id: songAuthors
                color: "white"
                width: parent.width
                height: parent.height
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }



        Item{
            Layout.preferredWidth: parent.width * 0.33
            Layout.preferredHeight: parent.height

            Text {
                id: songAlbum
                //text: album
                color: "white"
                width:parent.width
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight

            }
        }


    }


}


