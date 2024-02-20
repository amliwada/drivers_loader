#ifndef DRIVERS_LOADER_COMMAND_HPP
#define DRIVERS_LOADER_COMMAND_HPP

#include <QString>
#include <QList>

namespace drivers_loader
{
    class command
    {
    public:
        command(QString name) noexcept;

        void add_parameter(QString parameter);

        QString const& get_name() const noexcept;
        QString get_parameters_string() const noexcept;

    private:
        QString _name;
        QList<QString> _parameters;
    };
}

#endif