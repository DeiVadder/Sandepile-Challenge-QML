import QtQuick 2.9

Item {
    property alias color: grainColor.color
    property alias text: legendText.text

    width: grainColor.width + (legendText.contentWidth *1.2)
    height: 20

    anchors.margins: 5

    Rectangle{
        id: grainColor

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 0

        border.color: "white"
        border.width: 1

        width: height
    }

    Text{
        id: legendText

        anchors.left: grainColor.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.leftMargin: 2

        color: "white"
        verticalAlignment: Qt.AlignVCenter
    }
}
