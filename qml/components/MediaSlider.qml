pragma ComponentBehavior: Bound

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

            //SONG IMAGE AND COVER ART
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
                        source: "image://coverArt/" + GlobalSingleton.playbackManager.mediaPlayer.album + "/" + GlobalSingleton.playbackManager.mediaPlayer.albumArtists.join("++?")
                        sourceSize.width: 80
                        sourceSize.height: 80
                        asynchronous: true

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            source: songArt
                            x: songArt.x
                            y: songArt.y
                            width: songArt.width
                            height: songArt.height
                            autoPaddingEnabled: true
                            shadowEnabled: true
                            shadowVerticalOffset: 5
                            shadowHorizontalOffset: 2
                            
                        }

                        Connections{
                            target: GlobalSingleton.playbackManager.mediaPlayer
                            function onCoverArtChanged(){
                                songArt.source = "image://coverArt/" + GlobalSingleton.playbackManager.mediaPlayer.album + "/" + GlobalSingleton.playbackManager.mediaPlayer.albumArtists.join("%")
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
                            text: GlobalSingleton.playbackManager.mediaPlayer.trackTitle
                            Layout.preferredWidth: mediaInfo.width - songArt.width - 30
                            Layout.minimumWidth: 100

                            elide: Text.ElideRight

                            Connections{
                                target:GlobalSingleton.playbackManager.mediaPlayer
                                function onTrackTitleChanged(){
                                    songName.text = GlobalSingleton.playbackManager.mediaPlayer.trackTitle
                                }

                            }
                        }

                        Text{
                            id: songAuthors
                            color: "white"
                            Layout.preferredWidth: mediaInfo.width - songArt.width - 30
                            Layout.minimumWidth: 100
                            text: GlobalSingleton.playbackManager.mediaPlayer.features.length === 0 ? GlobalSingleton.playbackManager.mediaPlayer.leadingArtist  : GlobalSingleton.playbackManager.mediaPlayer.leadingArtist + " feat. " + GlobalSingleton.playbackManager.mediaPlayer.features.join(", ")
                            elide: Text.ElideRight

                            Connections{
                                target: GlobalSingleton.playbackManager.mediaPlayer
                                function onLeadingArtistChanged(){
                                    songAuthors.text = GlobalSingleton.playbackManager.mediaPlayer.features.length === 0 ? GlobalSingleton.playbackManager.mediaPlayer.leadingArtist  : GlobalSingleton.playbackManager.mediaPlayer.leadingArtist + " feat. " + GlobalSingleton.playbackManager.mediaPlayer.features.join(", ")
                                }
                            }
                        }

                        Item{
                            Layout.fillWidth: true
                        }

                    }
                }

            }

            //SONG CONTROLS
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
                                property bool shuffle: GlobalSingleton.playbackManager.nowPlaying.shuffle

                                id: shuffleSongs
                                anchors.centerIn: parent
                                height: 30
                                width: 30
                                source: shuffle == true ? "qrc:/resource/ui/assets/shuffle_on.png" : "qrc:/resource/ui/assets/shuffle.png"

                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    source: shuffleSongs
                                    x: shuffleSongs.x
                                    y: shuffleSongs.y
                                    width: shuffleSongs.width
                                    height: shuffleSongs.height
                                    autoPaddingEnabled: true
                                    shadowEnabled: true
                                    shadowVerticalOffset: 5
                                    shadowHorizontalOffset: 1
                                    
                                }

                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: shuffleSongs.scale = 1.2
                                    onExited: shuffleSongs.scale = 1.0

                                    onClicked : {
                                        if(!shuffleSongs.shuffle){
                                            shuffleSongs.source = "qrc:/resource/ui/assets/shuffle_on.png"
                                            GlobalSingleton.playbackManager.nowPlaying.setShuffle(true)
                                        }
                                        else{
                                            shuffleSongs.source = "qrc:/resource/ui/assets/shuffle.png"
                                            GlobalSingleton.playbackManager.nowPlaying.setShuffle(false)
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

                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    source: previousBtn
                                    x: previousBtn.x
                                    y: previousBtn.y
                                    width: previousBtn.width
                                    height: previousBtn.height
                                    autoPaddingEnabled: true
                                    shadowEnabled: true
                                    shadowVerticalOffset: 5
                                    shadowHorizontalOffset: 1
                                    
                                }

                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: previousBtn.scale = 1.2
                                    onExited: previousBtn.scale = 1.0
                                    onClicked: {
                                        GlobalSingleton.playbackManager.mediaPlayer.previousClicked()
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

                                Layout.preferredHeight: 40
                                Layout.preferredWidth: 40

                                anchors.centerIn: parent
                                
                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    source: playBtn
                                    x: playBtn.x
                                    y: playBtn.y
                                    width: playBtn.width
                                    height: playBtn.height
                                    autoPaddingEnabled: true
                                    shadowEnabled: true
                                    shadowVerticalOffset: 5
                                    shadowHorizontalOffset: 1
                                    
                                }

                                Shortcut{
                                    sequence: "Space"
                                    onActivated: GlobalSingleton.playbackManager.mediaPlayer.togglePlayState()
                                }


                                MouseArea {
                                    id: playBtnMA
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: playBtn.scale = 1.2
                                    onExited: playBtn.scale = 1.0
                                    onClicked: {
                                        GlobalSingleton.playbackManager.mediaPlayer.togglePlayState()
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
                                    target: GlobalSingleton.playbackManager.mediaPlayer
                                    function onUpdateUI(){
                                        if(GlobalSingleton.playbackManager.mediaPlayer.playing) {
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

                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    source: nextBtn
                                    x: nextBtn.x
                                    y: nextBtn.y
                                    width: nextBtn.width
                                    height: nextBtn.height
                                    autoPaddingEnabled: true
                                    shadowEnabled: true
                                    shadowVerticalOffset: 5
                                    shadowHorizontalOffset: 1
                                    
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: nextBtn.scale = 1.2
                                    onExited: nextBtn.scale = 1.0
                                    onClicked:{
                                        GlobalSingleton.playbackManager.mediaPlayer.nextClicked()
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
                                property bool repeat : GlobalSingleton.playbackManager.mediaPlayer.repeat

                                id: repeatSongs
                                height: 30
                                width: 30
                                source: repeat == true ? "qrc:/resource/ui/assets/repeat_individual.png" : "qrc:/resource/ui/assets/repeat.png"
                                anchors.centerIn: parent

                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    source: repeatSongs
                                    anchors.fill: repeatSongs
                                    autoPaddingEnabled: true
                                    shadowEnabled: true
                                    shadowVerticalOffset: 5
                                    shadowHorizontalOffset: 1
                                    
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onEntered: repeatSongs.scale = 1.2
                                    onExited: repeatSongs.scale = 1.0

                                    onClicked  : {
                                        if(!repeatSongs.repeat){
                                            repeatSongs.source = "qrc:/resource/ui/assets/repeat_individual.png"
                                            repeatSongs.repeat = true
                                            GlobalSingleton.playbackManager.mediaPlayer.repeat = repeatSongs.repeat

                                        }
                                        else{
                                            repeatSongs.source = "qrc:/resource/ui/assets/repeat.png"
                                            repeatSongs.repeat = false
                                            GlobalSingleton.playbackManager.mediaPlayer.repeat = repeatSongs.repeat
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
                                    target: GlobalSingleton.playbackManager.mediaPlayer
                                    function onPositionChanged(){
                                        elapsedTime.text = GlobalSingleton.playbackManager.mediaPlayer.genTime(GlobalSingleton.playbackManager.mediaPlayer.position)

                                    }
                                }


                            }
                        }

                        Slider {
                            id: control
                            from: 0
                            to: GlobalSingleton.playbackManager.mediaPlayer.duration
                            value: GlobalSingleton.playbackManager.mediaPlayer.position

                            Layout.preferredWidth: mediaControls.width-60
                            onValueChanged: {
                                GlobalSingleton.playbackManager.mediaPlayer.position = value
                            }

                            background: Rectangle {
                                    id: musicSliderBackground
                                    x: control.leftPadding
                                    y: control.topPadding + control.availableHeight / 2 - height / 2
                                    implicitWidth: 200
                                    implicitHeight: 4
                                    width: control.availableWidth
                                    height: implicitHeight
                                    radius: 2
                                    color: "#2e2e2e"

                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        source: musicSliderBackground
                                        anchors.fill: musicSliderBackground
                                        autoPaddingEnabled: true
                                        shadowEnabled: true
                                        shadowVerticalOffset: 5
                                        shadowHorizontalOffset: 1
                                        
                                    }

                                    Rectangle {
                                        width: control.visualPosition * parent.width
                                        height: parent.height
                                        color: "#606060"
                                        radius: 2
                                    }
                                }

                                handle: Rectangle {
                                    id: handle
                                    x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
                                    y: control.topPadding + control.availableHeight / 2 - height / 2
                                    implicitWidth: 16
                                    implicitHeight: 16
                                    radius: 8
                                    color: "#606060"

                                    layer.enabled: true
                                    layer.effect: MultiEffect {
                                        source: handle
                                        anchors.fill: handle
                                        autoPaddingEnabled: true
                                        shadowEnabled: true
                                        shadowVerticalOffset: 5
                                        shadowHorizontalOffset: 1
                                        
                                    }
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
                                    target: GlobalSingleton.playbackManager.mediaPlayer
                                    function onDurationChanged(){
                                        songDuration.text = GlobalSingleton.playbackManager.mediaPlayer.genTime(GlobalSingleton.playbackManager.mediaPlayer.duration)

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

            //VOLUME ADJUSTMENT, NOW PLAYING AND AUDIO DEVICE SELECTION
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


                    Image{
                        id: nowPlayingImage
                        source: "qrc:/resource/ui/assets/now_playing.png"

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            source: nowPlayingImage
                            anchors.fill: nowPlayingImage
                            autoPaddingEnabled: true
                            shadowEnabled: true
                            shadowVerticalOffset: 5
                            shadowHorizontalOffset: 1
                            
                        }
                        anchors {
                            right: audioImage.left
                            rightMargin: 5
                            verticalCenter: parent.verticalCenter
                        }

                        Behavior on scale{
                            NumberAnimation{
                                duration: 400
                                easing.type: Easing.OutBack
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onPressedChanged: {
                                if(pressed){
                                    nowPlayingImage.scale = 0.9
                                }
                                else{
                                    nowPlayingImage.scale = 1
                                }
                            }

                            onClicked: nowPlayingPopup.open()
                        }

                        Popup{
                            id: nowPlayingPopup
                            width: 350
                            height: 450
                            padding: 0

                            parent: Overlay.overlay
                            x: parent.width - width - 50
                            y: parent.height - height - 100

                            background: Item{}
                            contentItem: NowPlayingRect{}


                        }
                    }

                    Image{
                        id: audioImage
                        source: "qrc:/resource/ui/assets/audio_output.png"
                        sourceSize.height: 20
                        sourceSize.width: 20

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            source: audioImage
                            anchors.fill: audioImage
                            autoPaddingEnabled: true
                            shadowEnabled: true
                            shadowVerticalOffset: 5
                            shadowHorizontalOffset: 1
                            
                        }

                        anchors{
                            right: volumeStatus.left
                            rightMargin: 5
                            verticalCenter: parent.verticalCenter
                        }

                        AudioDevicesPopup{
                            id: audioDevicePopup
                        }

                        Behavior on scale{
                            NumberAnimation{
                                duration: 400
                                easing.type: Easing.OutBack
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked :{
                                audioDevicePopup.openPopup()
                            }

                            onPressedChanged :{
                                if(pressed){
                                    audioImage.scale = 0.7
                                }
                                else{
                                    audioImage.scale = 1.0
                                }
                            }



                        }
                    }

                    Image {
                        id: volumeStatus
                        source: volumeSlider.value === 0 ? "qrc:/resource/ui/assets/volumeMute.png" : "qrc:/resource/ui/assets/volumeLoud.png"
                        sourceSize.height: 20
                        sourceSize.width: 20

                        layer.enabled: true
                        layer.effect: MultiEffect {
                            source: volumeStatus
                            anchors.fill: volumeStatus
                            autoPaddingEnabled: true
                            shadowEnabled: true
                            shadowVerticalOffset: 5
                            shadowHorizontalOffset: 1
                            
                        }

                        anchors{
                            right: volumeSlider.left
                            verticalCenter: parent.verticalCenter
                        }

                    }


                    Slider{
                        id: volumeSlider
                        implicitWidth: parent.width * 0.3
                        value: GlobalSingleton.playbackManager.mediaPlayer.volume
                        from: 0
                        to: 1

                        anchors{
                            right: parent.right
                            verticalCenter: parent.verticalCenter
                            rightMargin: 20
                        }

                        background: Rectangle {
                                id: volumeSliderBackground
                                x: volumeSlider.leftPadding
                                y: volumeSlider.topPadding + volumeSlider.availableHeight / 2 - height / 2
                                implicitWidth: 200
                                implicitHeight: 4
                                width: volumeSlider.availableWidth
                                height: implicitHeight
                                radius: 2
                                color: "#2e2e2e"

                                layer.enabled: true
                                layer.effect: MultiEffect {
                                    source: volumeSliderBackground
                                    anchors.fill: volumeSliderBackground
                                    autoPaddingEnabled: true
                                    shadowEnabled: true
                                    shadowVerticalOffset: 5
                                    shadowHorizontalOffset: 1
                                    
                                }

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
                            GlobalSingleton.playbackManager.mediaPlayer.setVolume(volumeSlider.value)
                        }

                    }

                    Connections{
                        target: GlobalSingleton.playbackManager.mediaPlayer
                        function onVolumeChanged(){
                            volumeSlider.value = GlobalSingleton.playbackManager.mediaPlayer.volume
                        }
                    }
                }
            }
        }
    }
}






