import QtQuick
import QtQuick.Layouts
import Qt.labs.platform
import QtQuick.Controls.Basic
import QtQuick.Effects

import "./qml"
import "./qml/components"

import cplayer

//import com.c.MediaController

ApplicationWindow {
    width: 1280
    height: 720
    minimumWidth: 1024
    minimumHeight: 576
    visible: true
    title: qsTr("c")

    property alias mainWindow: mainContent
    property alias mainErrorPopup: errorPopup

    onClosing : {
        GlobalSingleton.save()
    }

    Rectangle {
        id: mainContent
        anchors.fill: parent
        color: "#131314"

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            MainWindow{
            }

            MediaSlider{
            }

        }


        ErrorPopup{
            id: errorPopup
        }

        MsgPopup{
            id: msgPopup
        }

    }

    Connections{
        target: GlobalSingleton.viewController

        function onShowMsg(msg){
            msgPopup.openPopup(msg)
        }
    }


   }


