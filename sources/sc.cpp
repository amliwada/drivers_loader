#include <drivers_loader/sc.hpp>
#include <drivers_loader/qml_engine.hpp>
#include <drivers_loader/shell_execute_exception.hpp>

drivers_loader::sc::sc(QObject* parent)
    : QObject{ parent }
{
    this->set_main_qml();

    if (this->is_main_qml_loading())
    {
        this->connect_to_main_qml_loaded_signal();
    }
    else
    {
        this->on_main_qml_loaded();
    }
}

void drivers_loader::sc::set_main_qml()
{
    this->_main_qml = &qml_engine::instance().get_main_qml();
}

bool drivers_loader::sc::is_main_qml_loading() const noexcept
{
    return this->_main_qml->isLoading();
}

void drivers_loader::sc::connect_to_main_qml_loaded_signal()
{
    this->main_qml_status_connection = QObject::connect(this->_main_qml, SIGNAL(statusChanged(QQmlComponent::Status)), this, SLOT(main_qml_status_changed(QQmlComponent::Status)));
}

void drivers_loader::sc::on_main_qml_status_changed(QQmlComponent::Status status)
{
    if (status == QQmlComponent::Status::Ready)
    {
        QObject::disconnect(this->main_qml_status_connection);

        this->on_main_qml_loaded();
    }
}

void drivers_loader::sc::on_main_qml_loaded()
{
    this->find_stack_view();
    this->find_file_loader();
    this->connect_to_file_selected_signal();
    this->find_settings();
    this->connect_to_settings();
    this->find_result_window();
}

void drivers_loader::sc::find_stack_view()
{
    this->_stack_view = qml_engine::instance().find_object_with_name("stack_view");
}

void drivers_loader::sc::find_file_loader()
{
    this->_file_loader = qml_engine::instance().find_object_with_name("file_loader");
}

void drivers_loader::sc::connect_to_file_selected_signal()
{
    QObject::connect(this->_file_loader, SIGNAL(fileSelected(QString)), this, SLOT(on_file_selected(QString)));
}

void drivers_loader::sc::on_file_selected(QString selected_file_url)
{
    if (this->is_supported_file(selected_file_url))
    {
        this->set_default_settings();
        this->move_to_settings();
    }
    else
    {
        this->on_bad_selected_file();
    }
}

bool drivers_loader::sc::is_supported_file(QString file_url)
{
    this->_selected_file_url = file_url;
    this->_selected_file_info = QFileInfo(file_url);
    return this->is_selected_file_has_supported_extention();
}

bool drivers_loader::sc::is_selected_file_has_supported_extention()
{
    return this->_selected_file_info.suffix() == "sys";
}

void drivers_loader::sc::on_bad_selected_file()
{
    QMetaObject::invokeMethod(this->_stack_view, "bad_selected_file");
}

void drivers_loader::sc::find_settings()
{
    this->_settings = qml_engine::instance().find_object_with_name("settings");
}

void drivers_loader::sc::set_default_settings()
{
    QMetaObject::invokeMethod(this->_settings, "set_path_to_driver", Q_ARG(QVariant, this->_selected_file_url.toLocalFile()));
    QMetaObject::invokeMethod(this->_settings, "set_driver_name", Q_ARG(QVariant, this->_selected_file_info.baseName()));
}

void drivers_loader::sc::connect_to_settings()
{
    QObject::connect(this->_settings, SIGNAL(newFileSelected(QString)), this, SLOT(on_file_reselected(QString)));
    QObject::connect(this->_settings, SIGNAL(startButtonClicked()), this, SLOT(on_start_button_clicked()));
}

void drivers_loader::sc::move_to_settings()
{
    QMetaObject::invokeMethod(this->_stack_view, "move_to_settings");
}

void drivers_loader::sc::find_result_window()
{
    this->_result_window = qml_engine::instance().find_object_with_name("result_window");
}

void drivers_loader::sc::on_start_button_clicked()
{
    try
    {
        this->execute_sc_create();
        this->execute_sc_start();
        this->show_success_result_message("Driver loaded");
    }
    catch (shell_execute_exception const& exception)
    {
        this->show_error_message();
    }
}

void drivers_loader::sc::execute_sc_create()
{
    auto sc_create_command{ this->make_sc_create_command() };
    this->_shell_execute.runas(sc_create_command);
    this->check_sc_create_exit_code();
}

drivers_loader::command drivers_loader::sc::make_sc_create_command()
{
    command sc_create_command{ "sc" };

    sc_create_command.add_parameter("create");

    auto driver_name{ this->get_settings_value("get_driver_name") };
    sc_create_command.add_parameter(driver_name);

    auto driver_type{ this->get_settings_value("get_driver_type") };
    sc_create_command.add_parameter("type=" + driver_type);

    auto load_type{ this->get_settings_value("get_load_type") };
    sc_create_command.add_parameter("start=" + load_type);

    sc_create_command.add_parameter("binPath=\"" + this->_selected_file_url.toLocalFile());

    return sc_create_command;
}

void drivers_loader::sc::check_sc_create_exit_code()
{
    auto exit_code{ this->_shell_execute.get_exit_code() };

    if (exit_code == 0)
    {
        return;
    }

    switch (exit_code)
    {
    case ERROR_SERVICE_EXISTS:
        return;
    }

    throw shell_execute_exception{ exit_code };
}

void drivers_loader::sc::show_error_message()
{
    auto exit_code{ this->_shell_execute.get_exit_code() };
    auto error_code_message = this->get_error_message_by_code(exit_code);
    QMetaObject::invokeMethod(this->_stack_view, "show_error_message", Q_ARG(QVariant, error_code_message));
}

QString drivers_loader::sc::get_error_message_by_code(int code)
{
    LPWSTR messageBuffer = nullptr;
    size_t size = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&messageBuffer, 0, NULL);
    auto error_code_message = QString::fromWCharArray(messageBuffer, size);
    LocalFree(messageBuffer);
    return error_code_message;
}

void drivers_loader::sc::execute_sc_start()
{
    auto sc_start_command{ this->make_sc_start_command() };
    this->_shell_execute.runas(sc_start_command);
    this->check_sc_start_exit_code();
}

drivers_loader::command drivers_loader::sc::make_sc_start_command()
{
    command sc_start_command{ "sc" };

    sc_start_command.add_parameter("start");

    auto driver_name{ this->get_settings_value("get_driver_name") };
    sc_start_command.add_parameter(driver_name);

    return sc_start_command;
}

void drivers_loader::sc::check_sc_start_exit_code()
{
    auto exit_code{ this->_shell_execute.get_exit_code() };

    if (exit_code == 0)
    {
        return;
    }

    switch (exit_code)
    {
    case ERROR_SERVICE_ALREADY_RUNNING:
        return;
    }

    throw shell_execute_exception{ exit_code };
}

void drivers_loader::sc::show_success_result_message(QString message)
{
    QMetaObject::invokeMethod(this->_stack_view, "show_success_result_message", Q_ARG(QVariant, message));
}

QString drivers_loader::sc::get_settings_value(char const* getter_name)
{
    QVariant settings_value;
    QMetaObject::invokeMethod(this->_settings, getter_name, Q_RETURN_ARG(QVariant, settings_value));
    return settings_value.toString();
}

void drivers_loader::sc::on_file_reselected(QString selected_file_url)
{
    if (this->is_supported_file(selected_file_url))
    {
        this->set_default_settings();
    }
    else
    {
        this->on_bad_selected_file();
    }
}