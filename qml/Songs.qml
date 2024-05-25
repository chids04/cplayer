import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import com.c.MediaController
import com.c.SongModel


Item {
    id:songsWindow
    // Layout.fillHeight: true
    // Layout.fillWidth: true


    ListView {
        id: songsListView
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10

        ScrollBar.vertical: ScrollBar {
            id:songScollbar
            policy: ScrollBar.AlwaysOn

            width: 15

            contentItem: Rectangle {
                implicitWidth: 15
                radius: 3
                color: "#606060"
            }

            background: Rectangle{
                color: "transparent"
            }
        }

        Component {
            id:songDelegate

            Rectangle {
                id: songView
                width: songsListView.width-23
                height: 100
                radius: 10
                color: index % 2 == 0 ? "#1e1f20" : "#131314"

                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: {
                        MediaPlayerController.setSong(filePath, title, artist, album, features)
                    }
                }

                RowLayout {

                    anchors{
                        verticalCenter: parent.verticalCenter
                    }

                    Image {
                        Layout.leftMargin: 10
                        source: "image://coverArt/" + album + "/" + artist
                        sourceSize.width: 80
                        sourceSize.height: 80
                    }
                    ColumnLayout {
                        Text {
                            text: title
                            font.bold: true
                            color: "white"
                        }
                        Text {
                            text: features.length === 0 ? artist  : artist + " feat. " + features.join(", ")
                            //text: artist
                            color: "white"
                        }
                        Text {
                            text: album
                            color: "white"
                        }
                    }
                }


            }
        }

        model: SongModel// This is the model exposed from C++
        delegate: songDelegate
        
    }
}
