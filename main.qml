import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

ApplicationWindow  {
    id:root
    visible: true
    width: 800
    height: 800
    title: qsTr("Sandpile")

    color:"black"

    Connections{
        target: liveImageProvider
        onImageChanged: img.reload()
    }

    onClosing:{
        if(SandPileModel.busy){
            close.accepted =  false
            SandPileModel.cancelRun()
        }else
            close.accepted = true;
    }

    Image {
        id: img
        property bool counter: false

        asynchronous: false
        source: "image://live/image"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        cache: false


        function reload() {
            counter = !counter
            source = "image://live/image?id=" + counter
        }
    }

    Text{
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        color: "white"
        font.pixelSize: 16
        text: SandPileModel.grainCount + " Grains fallen"
    }

    ColorLegend{
        id: grain0
        color: SandPileModel.getColor(0)
        text: "0 Grains"

        anchors.top: parent.top
        anchors.left: parent.left
    }

    ColorLegend{
        id: grain1
        color: SandPileModel.getColor(1)
        text: "1 Grain"

        anchors.top: grain0.bottom
        anchors.left: parent.left
    }

    ColorLegend{
        id: grain2
        color: SandPileModel.getColor(2)
        text: "2 Grains"

        anchors.top: grain1.bottom
        anchors.left: parent.left
    }

    ColorLegend{
        id: grain3
        color: SandPileModel.getColor(3)
        text: "3 Grains"
        anchors.top: grain2.bottom
        anchors.left: parent.left
    }
}
