import QtQuick
import QtQuick.Layouts

Item {
    id: folderView

    ColumnLayout{
        anchors.fill: parent

        Text{
            text: "Folders"
            font.bold: true
            font.pointSize: 100
            color: "white"
        }

        Item{
            Layout.fillHeight: true
        }
    }
}
