import QtQuick
import QtQuick.Layouts

import "../components"

import cplayer

Rectangle {
    id: songRect
    //width: songsListView.width-23
    radius: 10

    // property string songDelegateLeadingArtist
    // property int songDelegateIndex
    // property bool songFromAlbum
    // property list<string> songAlbumArtists

    // required property int index
    // required property int albumNum
    // required property string title
    // required property string artist
    // required property string album
    // required property list<string> features
    // required property list<string> albumArtists

    required property int index
    required property Song songObj

    property int highlightedIndex
    property bool isContextMenuOpen: false
    property bool notForAlbum: true

    //property Song song

    color: index % 2 == 0 ? "#1e1f20" : "#131314"


    property alias songDelegateWidth: songRect.width
    property alias songDelegateHeight: songRect.height
    property alias overlay: tintOverlay.color


    // property alias songDelegateNumber: songNumber.text
    // property alias songDelegateTitle: songTitle.text
    // property alias songDelegateAuthors: songAuthors.text
    // property alias songDelegateAlbum: songAlbum.text


    signal songDelegateClicked()
    signal songDelegateRightClicked()
    signal songDelegateDoubleClicked()


    Rectangle{
        id: tintOverlay
        anchors.fill: parent
        radius: songRect.radius
        color: "transparent"

        // color:{
        //     if(songRect.highlightedIndex === songRect.index){
        //         color = "#383838"
        //     }
        //     else{
        //         color = "transparent"
        //     }
        // }
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
            // if(songRect.highlightedIndex !== songRect.index){
            //     tintOverlay.color = "transparent"
            // }

            if(!songRect.isContextMenuOpen){
                tintOverlay.color = "transparent"
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
                tintOverlay.color = "#383838";
                songRect.isContextMenuOpen = true
                songRect.songDelegateRightClicked()

            }

        }

        // SongContextMenu{
        //     id:contextMenu
        //     onClosed: {
        //         songRect.isContextMenuOpen = false
        //         tintOverlay.color = "transparent"
        //     }
        // }


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

        Item {
            Layout.preferredWidth: parent.width * 0.33
            Layout.preferredHeight: parent.height

            RowLayout{
                anchors.fill: parent
                spacing: 0

                Text{
                    id: songNumber
                    Layout.preferredWidth: 40
                    text: songRect.notForAlbum ? songRect.index + 1 : songRect.songObj.trackNum
                    Layout.maximumWidth: 40
                    elide: Text.ElideRight
                    Layout.leftMargin: 10
                    horizontalAlignment: Text.AlignHCenter
                    color: "white"
                }

                Image {
                    id: albumImage
                    Layout.preferredWidth:60
                    Layout.preferredHeight:60
                    source: "image://coverArt/" + songRect.songObj.album + "/" + songRect.songObj.albumArtists.join('%')
                    sourceSize.width: 60
                    sourceSize.height: 60
                    Layout.rightMargin: 10
                    Layout.leftMargin: 10
                    asynchronous: true

                }

                Text {
                    id:songTitle
                    font.bold: true
                    text: songRect.songObj.title
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
                text: songRect.songObj.featuringArtists.length === 0 ? songRect.songObj.artist  : songRect.songObj.artist + " feat. " + songRect.songObj.featuringArtists.join(", ")
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
                text: songRect.songObj.album
                height: parent.height
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight

            }
        }


    }


}


