import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window
{
    id: root

    width: 600
    height: 680

    visible: true

    title: " ";

    color: "white"

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    StackView
    {
        id: stack_view

        objectName: "stack_view"

        anchors.fill: parent

        initialItem: file_loader

        function move_to_settings()
        {
            push(settings)
        }

        function show_success_result_message(message_text)
        {
            result_window.show_success_message(message_text)
            push(result_window)
        }

        function show_error_message(message_text)
        {
            result_window.show_error_message(message_text)
            push(result_window)
        }

        function bad_selected_file()
        {
            result_window.show_error_message("File extension not supported")
            push(result_window)
        }

        function show_file_loader()
        {
            replace(file_loader, file_loader)
        }
    }

    FileLoader
    {
        id: file_loader

        objectName: "file_loader"
        visible: false
    }

    ResultWindow
    {
        id: result_window

        objectName: "result_window"

        visible: false

        onClicked:
        {
            stack_view.show_file_loader();
        }
    }

    Settings
    {
        id: settings

        objectName: "settings"

        visible: false
    }
}