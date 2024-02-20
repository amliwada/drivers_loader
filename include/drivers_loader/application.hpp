#ifndef DRIVERS_LOADER_APPLICATION_HPP
#define DRIVERS_LOADER_APPLICATION_HPP

#include <QGuiApplication>

#include <drivers_loader/application_attributes_setter.hpp>
#include <drivers_loader/application_translator.hpp>
#include <drivers_loader/sc.hpp>

namespace drivers_loader
{
    class application
    {
    public:
        application(int argc, char *argv[]);

        int exec();

    private:
        application_attributes_setter _application_attributes_setter;
        application_translator* _application_translator;
        QGuiApplication _gui_application;
        sc* _sc;

    private:
        void set_icon();
    };
}

#endif