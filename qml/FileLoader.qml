import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.0


Item
{
    id: root

    signal fileSelected(string url)

    ColumnLayout
    {
        anchors.centerIn: parent

        spacing: 50

        Text
        {
            Layout.alignment : Qt.AlignHCenter

            font.pixelSize: 80
            font.family: "Arial"
            color: "#ff4149f2"

            text: "Hi(●•◡•●)"
        }

        ColumnLayout
        {
            Layout.alignment : Qt.AlignHCenter

            width: upload_button.width

            spacing: 12

            Button
            {
                id: upload_button

                text: "Upload driver"

                onClicked:
                {
                    file_dialog.open()
                }
            }

            Text
            {
                id: drop_file_text

                Layout.alignment : Qt.AlignHCenter

                font.family: "Arial"
                font.pixelSize: 14
                font.bold: true

                color: "#ff7f7f7f"

                text: "or drop a file"
            }
        }
    }

    FileDialog
    {
        id: file_dialog

        objectName: "file_dialog"

        title: "Choose a driver"

        selectExisting: true
        selectFolder: false
        selectMultiple: false

        nameFilters: [ "*.sys" ]

        onAccepted:
        {
            root.fileSelected(file_dialog.fileUrl)
        }
    }

    DropArea
    {
        anchors.fill: parent

        onDropped:
        {
            root.fileSelected(drop.text)
        }
    }
}