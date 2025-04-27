pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import cplayer

Popup {
    id: dlPopup
    modal: true
    focus: true
    padding: 20
    anchors.centerIn: Overlay.overlay
    dim: true

    property SCPlaylist playlistModel: new SCPlaylist

    enter: Transition {
                ParallelAnimation {
                    id: popIn
                    PropertyAnimation {
                        target: dlPopup
                        property: "scale"
                        from: 0.9
                        to: 1
                        duration: 50
                    }
                    PropertyAnimation {
                        target: dlPopup
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
                        target: dlPopup
                        property: "scale"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                    PropertyAnimation {
                        target: dlPopup
                        property: "opacity"
                        from: 1
                        to: 0.9
                        duration: 50
                    }
                }
            }

        background: Rectangle{
            anchors.fill: parent
            color: "#202020"
            border.color: "#2f3137"
            border.width: 2
            radius: 20
        }

        contentItem{
            Item{
                ListView{
                    id: searchResults
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.rightMargin: 5

                    clip: true

                    spacing: 5

                    Behavior on opacity{
                        NumberAnimation{
                            duration: 300
                            easing.type: Easing.InOutQuad
                        }
                    }

                    model: GlobalSingleton.downloadManager.scModel

                    delegate: Rectangle{
                        id: scSearchDelegate
                        width: searchResults.width
                        height: 90
                        color: "#1e1f20"
                        border.color: "#343434"
                        border.width: 2
                        radius: 5

                        required property string title
                        required property string artist
                        required property string artworkUrl
                        required property string itemType
                        required property int index

                        RowLayout{
                            anchors.fill: parent
                            anchors.leftMargin: 5
                            Image{
                                id: delegateImg
                                source: scSearchDelegate.artworkUrl
                                sourceSize.width: 80
                                sourceSize.height: 80
                                asynchronous: true
                            }

                            ColumnLayout{
                                Text {
                                    text: "<font color='grey'>title:</font> <font color='white'>" + scSearchDelegate.title + "</font>"
                                    // Enable rich text formatting
                                    textFormat: Text.RichText
                                    }

                                Text {
                                    text: "<font color='grey'>artist:</font> <font color='white'>" + scSearchDelegate.artist + "</font>"
                                    // Enable rich text formatting
                                    textFormat: Text.RichText
                                }

                                Text{
                                    //text: "<font color='grey'>type:</font> <font color='white'>" + scSearchDelegate.artist + "</font>"
                                    text: {
                                        if(scSearchDelegate.itemType == "track"){
                                            text = "<font color='grey'>type:</font> <font color='white'>track</font>"
                                        }
                                        else{
                                            text = "<font color='grey'>type:</font> <font color='white'>album/playlist</font>"
                                        }
                                    }

                                }
                            }

                            Item{
                                Layout.fillWidth: true
                            }

                            CButton{
                                buttonText: "download"
                                onButtonClicked: GlobalSingleton.downloadManager.scModel.download(scSearchDelegate.index);
                            }

                            CButton{
                                buttonText: "add to selection"
                            }

                        }

                    }
            }
            }

            
        }
}
