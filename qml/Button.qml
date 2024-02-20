import QtQuick 2.12

Item
{
    id: root

    readonly property color background_color: "#fff9f9f9"
    readonly property color focus_color: "#ff4149f2"
    readonly property color text_color: "#ff7f7f7f"
    readonly property color pressed_text_color: "#ff000000"

    property alias text: button_text.text

    signal clicked()

    width: button_text.width + 50
    height: button_text.height + 25

    Rectangle
    {
        id: button_background

        anchors.fill: root

        radius: 2

        color: root.background_color

        border.width: 1
        border.color: root.focus_color

        Behavior on border.color
        {
            ColorAnimation
            {
                duration: 100
            }
        }
    }

    Text
    {
        id: button_text

        anchors.centerIn: root

        font.family: "Arial"
        font.pixelSize: 14
        font.bold: true

        color: root.text_color

        font.capitalization: Font.AllUppercase

        Behavior on color
        {
            ColorAnimation
            {
                duration: 100
            }
        }
    }

    MouseArea {
        anchors.fill: root

        hoverEnabled: true

        onEntered:
        {
            button_background.border.color = Qt.darker(root.focus_color, 1.6)
            button_text.color = Qt.darker(root.text_color, 1.6)
        }

        onExited:
        {
            if (pressed)
            {
                button_text.color = root.focus_color
                button_background.border.color = root.focus_color
            }
            else
            {
                button_background.border.color = root.focus_color
                button_text.color = root.text_color
            }
        }

        onPressed:
        {
            button_background.border.color = root.pressed_text_color
            button_text.color = root.pressed_text_color
        }

        onReleased:
        {
            if (containsMouse)
            {
                root.clicked()

                button_background.border.color = Qt.darker(root.focus_color, 1.6)
                button_text.color = Qt.darker(root.focus_color, 1.6)
            }
            else
            {
                button_background.border.color = root.focus_color
                button_text.color = root.text_color
            }
        }
    }
}