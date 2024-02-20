#include <QIcon>
#include <QSurfaceFormat>
#include <QDebug>

#include <drivers_loader/application.hpp>
#include <drivers_loader/qml_engine.hpp>

drivers_loader::application::application(int argc, char *argv[])
    : _application_attributes_setter{ }
    , _application_translator{ new application_translator() }
    , _gui_application{ argc, argv }
{
    this->set_icon();

    qml_engine::instance().load_main_qml();

    this->_sc = new sc();
}

void drivers_loader::application::set_icon()
{
    QPixmap pixmap{ 1, 1 };
    pixmap.fill(Qt::white);
    QIcon icon{ pixmap };
    this->_gui_application.setWindowIcon(icon);
}

int drivers_loader::application::exec()
{
    return this->_gui_application.exec();
}