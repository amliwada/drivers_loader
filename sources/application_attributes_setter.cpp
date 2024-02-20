#include <QGuiApplication>

#include <drivers_loader/application_attributes_setter.hpp>

drivers_loader::application_attributes_setter::application_attributes_setter()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
}