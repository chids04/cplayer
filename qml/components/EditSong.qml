pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic


Popup {
    id: popUp
    //width: 660
    //height: 500
    modal: true
    focus: true
    dim: true
    parent: Overlay.overlay
    padding: 8

    x: Math.round((parent.width - implicitWidth) / 2)
    y: Math.round((parent.height - implicitHeight) / 2) - 10

    property string songTitle
    property string songAlbum
    property string songLeadingArtist
    property list<string> songAlbumArtists
    property list<string> songFeatures
    property int songTrackNum
    property string songGenre
    property int songYear
    property bool hasCover : false

    property Song songObj

    property list<string> features: songLeadingArtist.split("/")


    function openPopup(song){
        songTitle = song.title
        songAlbum = song.album
        songLeadingArtist = song.artist
        songAlbumArtists = song.albumArtists
        songFeatures = song.featuringArtists
        songTrackNum = song.trackNum
        songGenre = song.genre
        songYear = song.year
        songObj = song

        GlobalSingleton.songManager.setFeaturesToEdit(song.featuringArtists)
        GlobalSingleton.songManager.setAlbumArtistsToEdit(song.albumArtists)
        popUp.open()

    }

    enter: Transition {
        ParallelAnimation {
            id: popIn
            PropertyAnimation {
                target: popUp
                property: "scale"
                from: 0.9
                to: 1
                duration: 50
            }
            PropertyAnimation {
                target: popUp
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
                target: popUp
                property: "scale"
                from: 1
                to: 0.9
                duration: 50
            }
            PropertyAnimation {
                target: popUp
                property: "opacity"
                from: 1
                to: 0.9
                duration: 50
            }
        }
    }

    background: Rectangle {
        id: popUpDelegate
        anchors.fill: parent
        color: "#202020"
        radius: 5

        border.color: "#424345"
        border.width: 5
    }

    contentItem: Item{
        //width: popUp.width
        //height: popUp.height-40

        implicitWidth: 700
        implicitHeight: childrenRect.height
        ColumnLayout{
            anchors.fill: parent

            RowLayout{
                Layout.fillWidth: true

                Image{
                    id: songImg
                    source: "image://coverArt/" + popUp.songAlbum + "/" + popUp.songAlbumArtists.join('%')
                    sourceSize.height: 70
                    sourceSize.width: 70
                }

                CButton{
                    buttonText: "select Image"
                    onButtonClicked: imageFileDialog.open()
                    buttonTextSize: 10
                }

                CButton{
                    buttonText: "import details from album"
                    onButtonClicked: albumInfo.openPopup()
                    buttonTextSize: 10

                }

                AlbumInfo{
                    id: albumInfo

                    onAlbumSelected: (album) => {
                        genreText.text = album.genre
                        albumText.text = album.name
                        yearText.text = album.year
                        songImg.source = "image://coverArt/" + album.name + "/" + album.artist.join('%')

                        GlobalSingleton.songManager.setAlbumArtistsToEdit(album.artist)

                    }
                }
            }

            RowLayout{
                Layout.fillWidth: true
                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "track num"
                        font.bold: true
                        anchors.centerIn: parent
                        color: "white"
                    }
                }

                TextField{
                    id: trackNumText
                    text: popUp.songTrackNum
                    color: "white"
                    validator: IntValidator { bottom:0 }
                    horizontalAlignment: TextField.AlignHCenter
                    Layout.preferredWidth: trackNumTextmetric.width + 20
                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }

                    TextMetrics{
                        id: trackNumTextmetric
                        text: trackNumText.text
                    }
                }


            }
            RowLayout{
                Layout.fillWidth: true
                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "genre"
                        anchors.centerIn: parent
                        font.bold: true
                        color: "white"
                    }
                }

                TextField{
                    id: genreText
                    Layout.fillWidth: true
                    text: popUp.songGenre
                    color: "white"

                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }
                }


            }
            RowLayout{
                Layout.fillWidth: true
                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "year"
                        font.bold: true
                        anchors.centerIn: parent
                        color: "white"
                    }
                }

                TextField{
                    id: yearText
                    Layout.fillWidth: true
                    text: popUp.songYear
                    validator: IntValidator { bottom:0 }
                    color: "white"
                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }
                }


            }

            RowLayout{
                Layout.fillWidth:true
                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "title"
                        font.bold: true
                        anchors.centerIn: parent
                        color: "white"
                    }
                }

                TextField{
                    id: titleText
                    Layout.fillWidth: true
                    text: popUp.songTitle
                    color: "white"
                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }
                }
            }

            RowLayout{
                Layout.fillWidth:true

                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "artist"
                        font.bold: true
                        color: "white"
                        anchors.centerIn: parent
                    }
                }

                TextField{
                    id: leadingArtistText
                    Layout.fillWidth: true
                    text: popUp.songLeadingArtist
                    color: "white"
                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }
                }
            }
            RowLayout{
                Layout.fillWidth:true

                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "album"
                        font.bold: true
                        color: "white"
                        anchors.centerIn: parent
                    }
                }

                TextField{
                    id: albumText
                    Layout.fillWidth: true
                    text: popUp.songAlbum
                    color: "white"
                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }
                }
            }

            RowLayout{
                id: featuresRow
                Layout.fillWidth: true

                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "features"
                        font.bold: true
                        color: "white"
                        anchors.centerIn: parent
                    }
                }



                TextField{
                    id: featureToAdd
                    Layout.fillWidth: true
                    Layout.preferredWidth: 80
                    placeholderText: "add feature"
                    placeholderTextColor: "#606060"
                    color: "white"
                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }
                }

                CButton{
                    buttonText: "add feature"
                    buttonTextSize: 10
                    //onButtonClicked : popUp.features.append("test")
                    onButtonClicked: GlobalSingleton.songManager.insertFeature(featureToAdd.text)

                }

                ListView{
                    id: featuresList
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 60
                    clip: true
                    model: visualModel

                    ScrollBar.vertical: ScrollBar {
                        id:songScrollbar
                        policy: ScrollBar.AlwaysOn

                        width: 10

                        contentItem: Rectangle {
                            implicitWidth: 15
                            radius: 3
                            color: "#606060"
                        }

                        background: Rectangle{
                            color: "transparent"
                        }
                    }

                }

                DelegateModel {
                    id: visualModel

                    model: GlobalSingleton.songManager.featuresList
                    delegate: dragDelegate

                }



            }

            RowLayout{
                id: albumArtistsRow
                Layout.topMargin: 5
                Layout.fillWidth: true

                Item{
                    Layout.preferredWidth: 80

                    Text{
                        text: "album artists"
                        font.bold: true
                        color: "white"
                        font.pointSize: 9
                        anchors.centerIn: parent
                    }
                }

                TextField{
                    id: artistAdd
                    Layout.fillWidth: true
                    Layout.preferredWidth: 80
                    placeholderText: "add artist"
                    placeholderTextColor: "#606060"
                    color: "white"
                    background: Rectangle{
                        border.color: "#343434"
                        border.width: 2
                        color: "#232425"
                        radius: 10
                    }
                }

                CButton{
                    buttonText: "add artist"
                    buttonTextSize: 10
                    //onButtonClicked : popUp.features.append("test")
                    onButtonClicked: GlobalSingleton.songManager.insertArtist(artistAdd.text)

                }

                ListView{
                    id: artistList
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 60
                    clip: true
                    model: artistModel

                    ScrollBar.vertical: ScrollBar {
                        id: artistScrollbar
                        policy: ScrollBar.AlwaysOn

                        width: 10

                        contentItem: Rectangle {
                            implicitWidth: 15
                            radius: 3
                            color: "#606060"
                        }

                        background: Rectangle{
                            color: "transparent"
                        }
                    }

                }

                DelegateModel {
                    id: artistModel

                    model: GlobalSingleton.songManager.albumArtistsList
                    delegate: dragArtistDelegate

                }



            }

            CButton{
                buttonText: "save"
                Layout.alignment: Qt.AlignRight

                onButtonClicked: {
                    GlobalSingleton.songManager.saveChanges(popUp.songObj, titleText.text.trim(), leadingArtistText.text.trim(), albumText.text.trim(),
                                                            genreText.text.trim(), parseInt(yearText.text.trim()), parseInt(trackNumText.text.trim()), songImg.source)

                    popUp.close()
                }
            }
        }

        FileDialog{
            id: imageFileDialog
            title: "select song cover img"
            nameFilters: ["Image files (*.png *.jpg *.jpeg *.bmp)"]

            onAccepted: {
                popUp.hasCover = true
            }

        }

    }

    Component {
        id: dragDelegate

        MouseArea {
            id: dragArea

            property bool held: false
            required property int index
            required property string display

            //hoverEnabled: true
            anchors {
                left: parent?.left
                right: parent?.right
                leftMargin: 10
                rightMargin: songScrollbar.width + 5
            }
            height: content.height

            drag.target: held ? content : undefined
            drag.axis: Drag.YAxis

            onPressed: held = true
            onReleased: held = false


            onPositionChanged: {
                featuresList.positionViewAtIndex(featuresList.indexAt(x,y), ListView.Center)
            }

            Rectangle {
                id: content
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                width: dragArea.width

                height: 30
                border.color: "#343434"
                border.width: 2
                radius: 10

                color: dragArea.held ? "#6e7173" : "transparent"
                Behavior on color { ColorAnimation { duration: 100 } }


                Drag.active: dragArea.held
                Drag.source: dragArea
                Drag.hotSpot.x: width / 2
                Drag.hotSpot.y: height / 2

                states: State {
                    when: dragArea.held

                    ParentChange {
                        target: content
                        parent: featuresList
                    }
                    AnchorChanges {
                        target: content
                        anchors {
                            horizontalCenter: undefined
                            verticalCenter: undefined
                        }
                    }
                }

                RowLayout{
                    anchors.fill: parent

                    Image{
                        id: xBtn
                        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                        sourceSize.height: 15
                        sourceSize.width: 15
                        source: "qrc:/resource/ui/assets/x.png"

                        MouseArea{
                            anchors.fill: parent
                            onClicked: GlobalSingleton.songManager.removeFeature(dragArea.index)
                        }
                    }

                    Text{
                        elide: Text.ElideRight
                        Layout.fillWidth: true
                        Layout.leftMargin: 3
                        text: dragArea.display
                        color: "white"
                    }
                }

            }
            DropArea {
                anchors {
                    fill: parent
                    margins: 10
                }

                onEntered: (drag) => {
                    let src_index = drag.source.DelegateModel.itemsIndex
                    let target_index = dragArea.DelegateModel.itemsIndex
                    //dragDelegate.itemModel.items.move(src_index, target_index)
                    visualModel.items.move(src_index, target_index)
                    GlobalSingleton.songManager.moveFeature(src_index, target_index)

                    //GlobalSingleton.playbackManager.nowPlaying.moveSong(src_index, target_index)



                }
            }
        }
    }

    Component {
        id: dragArtistDelegate

        MouseArea {
            id: dragArtistArea

            property bool held: false
            required property int index
            required property string display

            hoverEnabled: true
            anchors {
                left: parent?.left
                right: parent?.right
                leftMargin: 10
                rightMargin: artistScrollbar.width + 5
            }
            height: artistContent.height

            drag.target: held ? artistContent : undefined
            drag.axis: Drag.YAxis

            onPressed: held = true
            onReleased: held = false


            onPositionChanged: {
                artistList.positionViewAtIndex(artistList.indexAt(x,y), ListView.Center)
            }

            Rectangle {
                id: artistContent
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                width: dragArtistArea.width

                height: 30
                border.color: "#343434"
                border.width: 2
                radius: 10

                color: dragArtistArea.held ? "#6e7173" : "transparent"
                Behavior on color { ColorAnimation { duration: 100 } }


                Drag.active: dragArtistArea.held
                Drag.source: dragArtistArea
                Drag.hotSpot.x: width / 2
                Drag.hotSpot.y: height / 2

                states: State {
                    when: dragArtistArea.held

                    ParentChange {
                        target: artistContent
                        parent: artistList
                    }
                    AnchorChanges {
                        target: artistContent
                        anchors {
                            horizontalCenter: undefined
                            verticalCenter: undefined
                        }
                    }
                }

                RowLayout{
                    anchors.fill: parent

                    Image{
                        id: xBtnArtist
                        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                        sourceSize.height: 15
                        sourceSize.width: 15
                        source: "qrc:/resource/ui/assets/x.png"

                        MouseArea{
                            anchors.fill: parent
                            onClicked: GlobalSingleton.songManager.removeArtist(dragArtistArea.index)
                        }
                    }

                    Text{
                        elide: Text.ElideRight
                        Layout.fillWidth: true
                        Layout.leftMargin: 3
                        text: dragArtistArea.display
                        color: "white"
                    }
                }

            }
            DropArea {
                anchors {
                    fill: parent
                    margins: 10
                }

                onEntered: (drag) => {
                    let src_index = drag.source.DelegateModel.itemsIndex
                    let target_index = dragArtistArea.DelegateModel.itemsIndex
                    //dragArtistDelegate.itemModel.items.move(src_index, target_index)
                    artistModel.items.move(src_index, target_index)
                    GlobalSingleton.songManager.moveArtist(src_index, target_index)

                    //GlobalSingleton.playbackManager.nowPlaying.moveSong(src_index, target_index)

                }
            }
        }
    }
}
