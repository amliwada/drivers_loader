#ifndef DRIVERS_LOADER_SHELL_EXECUTE_EXCEPTION_HPP
#define DRIVERS_LOADER_SHELL_EXECUTE_EXCEPTION_HPP

#include <windows.h>

#include <QString>

namespace drivers_loader
{
    class shell_execute_exception
    {
    public:
        shell_execute_exception(DWORD code) noexcept;

        DWORD get_code() const noexcept;

    private:
        DWORD _code;
    };
}

#endif