import QtQuick 2.12

Item
{
    id: root

    property alias text: input.text

    height: 50

    Rectangle
    {
        id: input_area

        anchors.fill: parent

        border.width: 2
        radius: 5
        border.color: input.focus ? "#ff4149f2" : "#ff000000"
    }

    TextInput
    {
        id: input

        width: parent.width - 40
        anchors.centerIn: parent
        anchors.margins: 10

        font.family: "Arial"
        font.pixelSize: 14

        selectedTextColor: "#ffffffff"
        selectionColor: "#ff4149f2"
        selectByMouse: true
    }
}