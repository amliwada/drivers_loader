#ifndef DRIVERS_LOADER_QML_ADAPTER_HPP
#define DRIVERS_LOADER_QML_ADAPTER_HPP

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>

namespace drivers_loader
{
    class qml_engine
    {
    public:
        void operator=(qml_engine const&) = delete;

        static qml_engine& instance() noexcept;

        void load_main_qml();

        void retranslate();

        QObject* find_object_with_name(QString object_name);

        QQmlComponent const& get_main_qml() const noexcept;

    private:
        QQmlApplicationEngine _engine;
        QQmlComponent _main_qml;
        QObject* _main_window;

    private:
        qml_engine();
        ~qml_engine() = default;

        void register_qml_types();
    };
}

#endif