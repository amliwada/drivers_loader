import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.0

Item
{
    id: root

    signal newFileSelected(string url)
    signal startButtonClicked()

    function set_path_to_driver(path)
    {
        path_to_driver.text = path
    }

    function set_driver_name(name)
    {
        driver_name_input.text = name
    }

    function get_driver_name()
    {
        return driver_name_input.text
    }

    function get_driver_type()
    {
        return driver_type.checked_button
    }

    function get_load_type()
    {
        return load_type.checked_button
    }

    ColumnLayout
    {
        anchors.centerIn: parent

        spacing: 50

        RowLayout
        {
            spacing: 50

            Rectangle
            {
                id: path_area

                width: 300
                height: 50

                Text
                {
                    id: path_to_driver

                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter

                    width: 300

                    font.family: "Arial"
                    font.pixelSize: 14
                    elide: Text.ElideMiddle
                    textFormat: Text.AutoText
                }
            }

            Button
            {
                Layout.alignment : Qt.AlignHCenter

                text: "Other"

                onClicked:
                {
                    file_dialog.open();
                }
            }
        }

        ColumnLayout
        {
            Text
            {
                font.family: "Arial"
                font.pixelSize: 14

                text: "Name: "
            }

            Input
            {
                id: driver_name_input

                Layout.fillWidth: true
            }
        }

        ColumnLayout
        {
            Text
            {
                font.family: "Arial"
                font.pixelSize: 14

                text: "Type: "
            }

            GridLayout
            {
                columns: 5

                RadioButton
                {
                    id: driver_type

                    model:
                    [
                        "own", "share", "kernel", "filesys", "rec", "adapt", "interact"
                    ]

                    checked_button: "kernel"
                }

            }
        }

        ColumnLayout
        {
            Text
            {
                font.family: "Arial"
                font.pixelSize: 14

                text: "Start: "
            }

            GridLayout
            {
                columns: 5

                RadioButton
                {
                    id: load_type

                    model:
                    [
                        "boot", "system", "auto", "demand", "disabled"
                    ]

                    checked_button: "demand"
                }

            }
        }

        Button
        {
            Layout.alignment : Qt.AlignHCenter

            text: "Start"

            onClicked:
            {
                root.startButtonClicked()
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

        nameFilters: [ "*.sys, *.exe" ]

        onAccepted:
        {
            root.newFileSelected(file_dialog.fileUrl)
        }
    }

    DropArea
    {
        anchors.fill: parent

        onDropped:
        {
            root.newFileSelected(drop.text)
        }
    }
}