#ifndef DRIVERS_LOADER_SC_START_HPP
#define DRIVERS_LOADER_SC_START_HPP

#include <QObject>
#include <QQmlComponent>
#include <QFileInfo>

#include <drivers_loader/command.hpp>
#include <drivers_loader/shell_execute.hpp>

namespace drivers_loader
{
    class sc
        : QObject
    {
        Q_OBJECT

    public:
        sc(QObject* parent = nullptr);

    private:
        QQmlComponent const* _main_qml;
        QMetaObject::Connection main_qml_status_connection;
        QUrl _selected_file_url;
        QFileInfo _selected_file_info;
        QObject* _stack_view;
        QObject* _file_loader;
        QObject* _settings;
        QObject* _result_window;
        shell_execute _shell_execute;

    private slots:
        void on_main_qml_status_changed(QQmlComponent::Status);
        void on_file_selected(QString selected_file_url);
        void on_file_reselected(QString selected_file_url);
        void on_start_button_clicked();

    private:
        void set_main_qml();
        void connect_to_main_qml_loaded_signal();
        bool is_main_qml_loading() const noexcept;
        void on_main_qml_loaded();
        void find_stack_view();
        void find_file_loader();
        void connect_to_file_selected_signal();
        bool is_supported_file(QString file_url);
        bool is_selected_file_has_supported_extention();
        void on_bad_selected_file();
        void find_settings();
        void set_default_settings();
        void connect_to_settings();
        void move_to_settings();
        void find_result_window();
        void execute_sc_create();
        command make_sc_create_command();
        void check_sc_create_exit_code();
        void show_error_message();
        QString get_error_message_by_code(int code);
        void execute_sc_start();
        command make_sc_start_command();
        void check_sc_start_exit_code();
        void show_success_result_message(QString message);
        QString get_settings_value(char const* getter_name);
    };
}

#endif