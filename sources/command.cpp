#include <drivers_loader/command.hpp>

drivers_loader::command::command(QString name) noexcept
    : _name{ std::move(name) }
{ }

void drivers_loader::command::add_parameter(QString parameter)
{
    this->_parameters.append(std::move(parameter));
}

QString const& drivers_loader::command::get_name() const noexcept
{
    return this->_name;
}

QString drivers_loader::command::get_parameters_string() const noexcept
{
    QString parameters_string;

    for (auto const& parameter : this->_parameters)
    {
        parameters_string += parameter + " ";
    }

    return parameters_string;
}