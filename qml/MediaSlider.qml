import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Effects

import cplayer

Item{
    Layout.fillWidth: true
    height: 100


    MultiEffect{
        source: mediaBar
        anchors.fill: mediaBar
        shadowBlur: 1
        shadowEnabled: true
        shadowColor: "#80000000"
        autoPaddingEnabled: true
        shadowVerticalOffset: -10

    }



    Rectangle {
        id: mediaBar
        anchors.fill: parent
        radius: 8
        color: "#1e1f20"

        RowLayout{

            anchors.fill: parent

            Rectangle{
                id: mediaInfo
                color: "transparent"
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.3


                RowLayout{
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    spacing: 10

                    Image {
                        id: songArt
                        Layout.preferredHeight: 80
                        Layout.preferredWidth: 80
                        Layout.alignment: Qt.AlignVCenter
                        //source: "qrc:/resource/ui/assets/unknownCover.png"
                        source: "image://coverArt/" + MusicHandler.mediaPlayerController.album + "/" + MusicHandler.mediaPlayerController.leadingArtist
                        sourceSize.width: 80
                        sourceSize.height: 80

                        Connections{
                            target: MusicHandler.mediaPlayerController
                            function onCoverArtChanged(){
                                songArt.source = "image://coverArt/" + MusicHandler.mediaPlayerController.album + "/" + MusicHandler.mediaPlayerController.leadingArtist
                            }
                        }
                    }

                    ColumnLayout{
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignVCenter

                        Text {
                            id: songName
                            color: "white"
                            font.bold: true
                            text: MusicHandler.mediaPlayerController.trackTitle
                            Layout.preferredWidth: mediaInfo.width - songArt.width - 30
                            Layout.minimumWidth: 100

                            elide: Text.ElideRight

                            Connections{
                                target: MusicHandler.mediaPlayerController
                                function onTrackTitleChanged(){
                                    songName.text = MusicHandler.mediaPlayerController.trackTitle
                                }

                            }
                        }

                        Text{
                            id: songAuthors
                            color: "white"
                            Layout.preferredWidth: mediaInfo.width - songArt.width - 30
                            Layout.minimumWidth: 100
                            text: MusicHandler.mediaPlayerController.features.length === 0 ? MusicHandler.mediaPlayerController.leadingArtist  : MusicHandler.mediaPlayerController.leadingArtist + " feat. " + MusicHandler.mediaPlayerController.features.join(", ")
                            elide: Text.ElideRight

                            Connections{
                                target: MusicHandler.mediaPlayerController
                                function onLeadingArtistChanged(){
                                    songAuthors.text = MusicHandler.mediaPlayerController.features.length === 0 ? MusicHandler.mediaPlayerController.leadingArtist  : MusicHandler.mediaPlayerController.leadingArtist + " feat. " + MusicHandler.mediaPlayerController.features.join(", ")
                                }
                            }
                        }

                        Item{
                            Layout.fillWidth: true
                        }

                    }
                }

            }

            Rectangle{
                id: mediaControls
                color: "transparent"
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.4


                ColumnLayout{
                    anchors.fill: parent
                    spacing: 0

                    RowLayout {
                        id: playbackControls

                        Layout.alignment: Qt.AlignHCenter
                        //spacing: 40
                        Layout.fillWidth: true

                        Item{
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Image {
                                property bool shuffle: false

                                id: shuffleSongs
                                anchors.centerIn: parent
                                height: 30
                                width: 30
                                source: "qrc:/resource/ui/assets/shuffle.png"

                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: shuffleSongs.scale = 1.2
                                    onExited: shuffleSongs.scale = 1.0

                                    onClicked : {
                                        if(!shuffleSongs.shuffle){
                                            shuffleSongs.source = "qrc:/resource/ui/assets/shuffle_on.png"
                                            shuffleSongs.shuffle = true
                                        }
                                        else{
                                            shuffleSongs.source = "qrc:/resource/ui/assets/shuffle.png"
                                            shuffleSongs.shuffle = false
                                        }
                                    }

                                    onPressedChanged: {
                                        if(pressed){
                                            shuffleSongs.scale = 0.9
                                        }
                                        else{
                                            shuffleSongs.scale = 1.2
                                        }
                                    }

                                }

                                Behavior on scale{
                                    NumberAnimation{
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }

                            }
                    }



                        Item{
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Image {
                                id: previousBtn
                                height: 30
                                width: 30
                                source: "qrc:/resource/ui/assets/previous.png"
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter

                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: previousBtn.scale = 1.2
                                    onExited: previousBtn.scale = 1.0
                                    onClicked: {
                                        MusicHandler.mediaPlayerController.previousClicked()
                                    }

                                    onPressedChanged:{
                                        if(pressed){
                                            previousBtn.scale = 0.9
                                        }
                                        else{
                                            previousBtn.scale = 1.2
                                        }
                                    }
                                }

                                Behavior on scale {
                                    NumberAnimation{
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }

                            }
                        }

                        Item{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Image {
                                id: playBtn
                                //source: "qrc:/resource/ui/assets/playBtn.png"
                                source: "qrc:/resource/ui/assets/playBtn.png"

                                sourceSize.width: 40
                                sourceSize.height: 40
                                anchors.centerIn: parent


                                MouseArea {
                                    id: playBtnMA
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: playBtn.scale = 1.2
                                    onExited: playBtn.scale = 1.0
                                    onClicked: {
                                        MusicHandler.mediaPlayerController.togglePlayState()
                                    }

                                    onPressedChanged: {
                                        if(pressed){
                                            playBtn.scale = 0.9
                                        }
                                        else{
                                            playBtn.scale = 1.2
                                        }
                                    }
                                }

                                Behavior on scale {
                                    NumberAnimation{
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }


                                Connections {
                                    target: MusicHandler.mediaPlayerController
                                    function onUpdateUI(){
                                        if(MusicHandler.mediaPlayerController.playing) {
                                            playBtn.source = "qrc:/resource/ui/assets/pauseBtn.png"
                                        }
                                        else{
                                            playBtn.source = "qrc:/resource/ui/assets/playBtn.png"
                                        }
                                    }
                                }

                            }
                        }



                        Item{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Image {
                                id: nextBtn
                                height: 30
                                width: 30
                                source: "qrc:/resource/ui/assets/next.png"
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: nextBtn.scale = 1.2
                                    onExited: nextBtn.scale = 1.0
                                    onClicked:{
                                        MusicHandler.mediaPlayerController.nextClicked()
                                    }

                                    onPressedChanged: {
                                        if(pressed){
                                            nextBtn.scale = 0.9
                                        }
                                        else{
                                            nextBtn.scale = 1.2
                                        }
                                    }
                                }

                                Behavior on scale {
                                    NumberAnimation{
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }

                            }
                        }



                        Item{
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Image{
                                property bool shuffle : false

                                id: repeatSongs
                                height: 30
                                width: 30
                                source: "qrc:/resource/ui/assets/repeat.png"
                                anchors.centerIn: parent

                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: repeatSongs.scale = 1.2
                                    onExited: repeatSongs.scale = 1.0

                                    onClicked  : {
                                        if(!repeatSongs.shuffle){
                                            repeatSongs.source = "qrc:/resource/ui/assets/repeat_individual.png"
                                            repeatSongs.shuffle = true
                                            MusicHandler.mediaPlayerController.onRepeatChanged(repeatSongs.shuffle)

                                        }
                                        else{
                                            repeatSongs.source = "qrc:/resource/ui/assets/repeat.png"
                                            repeatSongs.shuffle = false
                                            MusicHandler.mediaPlayerController.onRepeatChanged(repeatSongs.shuffle)
                                        }

                                    }

                                    onPressedChanged: {
                                        if(pressed){
                                            repeatSongs.scale = 0.9
                                        }
                                        else{
                                            repeatSongs.scale = 1.2
                                        }
                                    }

                                }

                                Behavior on scale{
                                    NumberAnimation{
                                        duration: 200
                                        easing.type: Easing.InOutQuad
                                    }
                                }
                            }
                        }


                    }
                    RowLayout{
                        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                        Layout.bottomMargin: 10
                        spacing: 10

                        Item{
                            Layout.preferredWidth: 30

                            Text{
                                id: elapsedTime
                                text: "00:00"
                                anchors.centerIn: parent
                                color: "white"

                                Connections{
                                    target: MusicHandler.mediaPlayerController
                                    function onPositionChanged(){
                                        elapsedTime.text = MusicHandler.mediaPlayerController.genTime(MusicHandler.mediaPlayerController.position)

                                    }
                                }


                            }
                        }

                        Slider {
                            id: control
                            from: 0
                            to: MusicHandler.mediaPlayerController.duration
                            value: MusicHandler.mediaPlayerController.position

                            Layout.preferredWidth: mediaControls.width-60
                            onValueChanged: {
                                MusicHandler.mediaPlayerController.position = value
                            }

                            background: Rectangle {
                                    x: control.leftPadding
                                    y: control.topPadding + control.availableHeight / 2 - height / 2
                                    implicitWidth: 200
                                    implicitHeight: 4
                                    width: control.availableWidth
                                    height: implicitHeight
                                    radius: 2
                                    color: "#2e2e2e"

                                    Rectangle {
                                        width: control.visualPosition * parent.width
                                        height: parent.height
                                        color: "#606060"
                                        radius: 2
                                    }
                                }

                                handle: Rectangle {
                                    x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
                                    y: control.topPadding + control.availableHeight / 2 - height / 2
                                    implicitWidth: 16
                                    implicitHeight: 16
                                    radius: 8
                                    color: "#606060"
                                }

                            }


                        Item{
                            Layout.preferredWidth: 30

                            Text{
                                height: 20
                                id: songDuration
                                text : "00:00"
                                anchors.centerIn: parent
                                color: "white"

                                Connections{
                                    target: MusicHandler.mediaPlayerController
                                    function onDurationChanged(){
                                        songDuration.text = MusicHandler.mediaPlayerController.genTime(MusicHandler.mediaPlayerController.duration)

                                    }

                                    function onResetDuration(){
                                        songDuration.text = "00:00"
                                    }
                                }
                            }
                        }
                    }

                }
            }

            Rectangle{
                id: extraControls
                color: "transparent"
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.3

                Rectangle{
                    height: parent.height
                    width: parent.width
                    anchors.centerIn: parent
                    color:"transparent"

                    Image {
                        id: volumeStatus
                        source: volumeSlider.value === 0 ? "qrc:/resource/ui/assets/volumeMute.png" : "qrc:/resource/ui/assets/volumeLoud.png"
                        sourceSize.height: 20
                        sourceSize.width: 20

                        anchors{
                            right: volumeSlider.left
                            verticalCenter: parent.verticalCenter
                        }
                    }

                    Slider{
                        id: volumeSlider
                        implicitWidth: parent.width * 0.3
                        value: MusicHandler.mediaPlayerController.volume
                        from: 0
                        to: 1

                        anchors{
                            right: parent.right
                            verticalCenter: parent.verticalCenter
                            rightMargin: 20
                        }

                        background: Rectangle {
                                x: volumeSlider.leftPadding
                                y: volumeSlider.topPadding + volumeSlider.availableHeight / 2 - height / 2
                                implicitWidth: 200
                                implicitHeight: 4
                                width: volumeSlider.availableWidth
                                height: implicitHeight
                                radius: 2
                                color: "#2e2e2e"

                                Rectangle {
                                    width: volumeSlider.visualPosition * parent.width
                                    height: parent.height
                                    color: "#606060"
                                    radius: 2
                                }
                            }

                        handle: Rectangle {
                            x: volumeSlider.leftPadding + volumeSlider.visualPosition * (volumeSlider.availableWidth - width)
                            y: volumeSlider.topPadding + volumeSlider.availableHeight / 2 - height / 2
                            implicitWidth: 10
                            implicitHeight: 10
                            radius: 5
                            color: "#606060"
                        }

                        onValueChanged: {
                            MusicHandler.mediaPlayerController.setVolume(volumeSlider.value)
                        }

                    }

                    Connections{
                        target: MusicHandler.mediaPlayerController
                        function onVolumeChanged(){
                            volumeSlider.value = MusicHandler.mediaPlayerController.volume
                        }
                    }
                }
            }
        }
    }
}






