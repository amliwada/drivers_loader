#include <drivers_loader/qml_engine.hpp>

drivers_loader::qml_engine& drivers_loader::qml_engine::instance() noexcept
{
    static qml_engine instance;
    return instance;
}

drivers_loader::qml_engine::qml_engine()
    : _main_qml{ &this->_engine, QUrl("qrc:/main.qml") }
{ }

void drivers_loader::qml_engine::load_main_qml()
{
    this->_main_window = this->_main_qml.create();
}

void drivers_loader::qml_engine::retranslate()
{
    this->_engine.retranslate();
}

QObject* drivers_loader::qml_engine::find_object_with_name(QString object_name)
{
    return this->_main_window->findChild<QObject*>(object_name);
}

QQmlComponent const& drivers_loader::qml_engine::get_main_qml() const noexcept
{
    return this->_main_qml;
}