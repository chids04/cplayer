pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import cplayer

Item {

    RectangleLoader{
        id: loadIcon
        anchors.centerIn: parent
        barCount: 5
        width: 60
        height: 60
        color: "#343434"
        visible: false
    }

    Connections{
        target: GlobalSingleton.downloadManager.scModel

        function onSearchStart(){
            searchResults.opacity = 0
            loadIcon.visible = true
        }

        function onSearchEnd(){
            searchResults.opacity = 1
            loadIcon.visible = false
        }
    }

    ColumnLayout{
        anchors.fill: parent


        TextField {
            id: textfield
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.preferredHeight: 40
            Layout.rightMargin: 10
            placeholderText: "search for a song.."
            placeholderTextColor: "white"
            color: "white"


            background: Rectangle{
                border.color: "#343434"
                border.width: 2
                color: "#232425"
                radius: 10
            }

        }

        CButton {
            buttonText: "search"
            onButtonClicked: GlobalSingleton.downloadManager.scModel.newSearch(textfield.text)
        }

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
                        onButtonClicked: GlobalSingleton.downloadManager.scModel.download(index);
                    }

                    CButton{
                        buttonText: "add to selection"
                    }

                }

            }
        }
    }
}

