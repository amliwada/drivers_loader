#include <drivers_loader/shell_execute_exception.hpp>

drivers_loader::shell_execute_exception::shell_execute_exception(DWORD code) noexcept
    : _code{ code }
{ }

DWORD drivers_loader::shell_execute_exception::get_code() const noexcept
{
    return this->_code;
}