#include <drivers_loader/application_translator.hpp>
#include <drivers_loader/qml_engine.hpp>

#include <QDir>
#include <QDebug>

drivers_loader::application_translator::application_translator()
{
    this->_translator = new QTranslator(this);
}

void drivers_loader::application_translator::translate_to_russian()
{
    QDir translations_dir = QDir(qApp->applicationDirPath()).absolutePath();
    this->_translator->load("drivers_loader_ru_RU", translations_dir.path());
    qApp->installTranslator(this->_translator);
    qml_engine::instance().retranslate();

    emit language_changed();
}