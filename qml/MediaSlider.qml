import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Effects
import com.c.MediaController


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

        // anchors {
        //     left: parent.left
        //     right: parent.right
        //     bottom: parent.bottom
        //     top: mainWindow.bottom
        // }

        // MultiEffect{
        //     source: mediaBar
        //     anchors.fill: mediaBar
        //     shadowBlur: 1.0
        //     shadowEnabled: true
        //     shadowColor: "black"
        // }

        RowLayout{

            anchors.fill: parent

            Rectangle{
                id: mediaInfo
                color: "transparent"
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.3

                Image {
                    id: songArt
                    height: 80
                    width: 80
                    source: "qrc:/resource/ui/assets/pika.png"
                    anchors{
                        left: parent.left
                        verticalCenter: parent.verticalCenter
                        leftMargin: 7
                    }

                    sourceSize.width: 80
                    sourceSize.height: 80

                    Connections{
                        target: MediaPlayerController
                        function onCoverArtChanged(){
                            songArt.source = "image://coverArt/" + MediaPlayerController.album + "/" + MediaPlayerController.leadingArtist
                        }
                    }



                }

                Column {
                    spacing: 5
                    anchors{
                        left: songArt.right
                        verticalCenter: parent.verticalCenter
                        leftMargin: 7
                    }

                    Text {
                        id: songName
                        text: "line 1"
                        color: "white"
                        font.bold: true

                        Connections{
                            target: MediaPlayerController
                            function onTrackTitleChanged(){
                                songName.text = MediaPlayerController.trackTitle
                            }

                        }
                    }

                    Text{
                        id: songAuthors
                        text: "line 2"
                        color: "white"

                        Connections{
                            target: MediaPlayerController
                            function onLeadingArtistChanged(){
                                songAuthors.text = MediaPlayerController.features.length === 0 ? MediaPlayerController.leadingArtist  : MediaPlayerController.leadingArtist + " feat. " + MediaPlayerController.features.join(", ")
                            }
                        }
                    }
                }
            }

            Rectangle{
                id: mediaControls
                color: "transparent"
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width * 0.4

                Rectangle{

                    height: childrenRect.height

                    anchors.centerIn: parent

                    RowLayout {
                        id: playbackControls
                        anchors{
                            top: parent.top
                            horizontalCenter: parent.horizontalCenter
                        }

                        spacing: 40

                        Image {
                            id: shuffleSongs
                            height: 30
                            width: 30
                            source: "qrc:/resource/ui/assets/shuffle.png"

                        }

                        Image {
                            id: previousBtn
                            height: 30
                            width: 30
                            source: "qrc:/resource/ui/assets/previous.png"
                        }

                        // MultiEffect{
                        //     source: playBtn
                        //     anchors.fill: playBtn
                        //     shadowBlur: 1
                        //     shadowEnabled: true
                        //     shadowColor: "#80000000"
                        //     autoPaddingEnabled: true
                        //     shadowHorizontalOffset: 15
                        //     shadowVerticalOffset: 11
                        // }

                        Image {
                            id: playBtn
                            source: "qrc:/resource/ui/assets/play.png"

                            MouseArea {
                                anchors.fill: parent

                                onClicked: {
                                    MediaPlayerController.togglePlayState()
                                }
                            }

                            Connections {
                                target: MediaPlayerController
                                function onUpdateUI(){
                                    if(MediaPlayerController.playing) {
                                        playBtn.source = "qrc:/resource/ui/assets/play.png"
                                    }
                                    else{
                                        playBtn.source = "qrc:/resource/ui/assets/pause.png"
                                    }
                                }
                            }

                        }

                        Image {
                            id: nextBtn
                            height: 30
                            width: 30
                            source: "qrc:/resource/ui/assets/next.png"
                        }

                        Image{
                            id: repeatSongs
                            height: 30
                            width: 30
                            source: "qrc:/resource/ui/assets/repeat.png"
                        }
                    }



                    Slider {
                        id: control
                        from: 0
                        to: MediaPlayerController.duration
                        value: MediaPlayerController.position
                        anchors{
                            top: playbackControls.bottom
                            topMargin: 15
                            horizontalCenter: parent.horizontalCenter
                        }

                        width: mediaControls.width
                        onValueChanged: {
                            MediaPlayerController.position = value
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
                                color: control.pressed ? "#f0f0f0" : "#f6f6f6"
                                border.color: "#bdbebf"
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
                        source: volumeSlider.value === 0 ? "qrc:/resource/ui/assets/mute.png" : "qrc:/resource/ui/assets/volume.png"

                        anchors{
                            right: volumeSlider.left
                            verticalCenter: parent.verticalCenter
                        }
                    }

                    Slider{
                        id: volumeSlider
                        implicitWidth: parent.width * 0.3
                        value: MediaPlayerController.volume
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
                            color: volumeSlider.pressed ? "#f0f0f0" : "#f6f6f6"
                            border.color: "#bdbebf"
                        }

                        onValueChanged: {
                            MediaPlayerController.setVolume(volumeSlider.value)
                        }

                    }

                    Connections{
                        target: MediaPlayerController
                        function onVolumeChanged(){
                            volumeSlider.value = MediaPlayerController.volume
                        }
                    }
                }

            }


        }

    }
}






