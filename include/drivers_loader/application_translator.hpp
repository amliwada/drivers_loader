#ifndef DRIVERS_LOADER_APPLICATION_TRANSLATOR_HPP
#define DRIVERS_LOADER_APPLICATION_TRANSLATOR_HPP

#include <QObject>
#include <QTranslator>
#include <QString>
#include <QGuiApplication>

namespace drivers_loader
{
    class application_translator
            : public QObject
    {
        Q_OBJECT

    public:
        application_translator();

        Q_INVOKABLE void translate_to_russian();

    signals:
        void language_changed();

    private:
        QTranslator* _translator;
    };
}

#endif