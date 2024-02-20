import QtQuick 2.12
import QtQuick.Layouts 1.12

Item
{
    id: root

    signal clicked()

    function show_error_message(message_text)
    {
        smile.text = "(´•︵•`)"

        message.text = message_text

        visible = true
    }

    function show_success_message(message_text)
    {
        smile.text = "ദ്ദി ˉ͈̀꒳ˉ͈́ )✧"

        message.text = message_text

        visible = true
    }

    ColumnLayout
    {
        anchors.centerIn: parent

        spacing: 30

        Text
        {
            id: smile

            Layout.alignment : Qt.AlignHCenter

            font.pixelSize: 80
            font.family: "Arial"
            color: "#ff4149f2"
        }

        Text
        {
            id: message

            Layout.alignment : Qt.AlignHCenter

            font.pixelSize: 20
            font.family: "Arial"
        }
    }

    Button
    {
        id: continue_button

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70

        text: "OK"

        onClicked:
        {
            root.clicked()
        }
    }
}