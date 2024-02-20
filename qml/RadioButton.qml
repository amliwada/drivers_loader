import QtQuick 2.12

Repeater
{
    id: root

    readonly property int button_size: 40
    readonly property color default_color: "#ffc0c0c0"
    readonly property color default_text_color: "#ff7f7f7f"
    readonly property color focused_text_color: Qt.darker(default_text_color, 1.6)
    readonly property color focus_color: "#ff4149f2"

    property string checked_button

    Rectangle
    {
        id: button

        width: button_text.width + root.button_size
        height: root.button_size

        radius: 10

        color: "#fff9f9f9"

        border.width: 2
        border.color: root.checked_button === root.model[index] ? root.focus_color : root.default_color

        Behavior on border.color
        {
            ColorAnimation
            {
                duration: 100
            }
        }

        Text
        {
            id: button_text

            anchors.centerIn: button

            font.family: "Verdana"
            font.pixelSize: 14

            color: root.checked_button === root.model[index] ? root.focus_color : root.default_text_color

            Behavior on color
            {
                ColorAnimation
                {
                    duration: 100
                }
            }

            text: root.model[index]
        }

        MouseArea
        {
            hoverEnabled: true

            anchors.fill: button

            onClicked:
            {
                root.checked_button = root.model[index]
            }
        }
    }
}