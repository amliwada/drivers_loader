#ifndef DRIVERS_LOADER_SHELL_EXECUTE_HPP
#define DRIVERS_LOADER_SHELL_EXECUTE_HPP

#include <windows.h>

#include <drivers_loader/command.hpp>

namespace drivers_loader
{
    class shell_execute
    {
    public:
        void runas(command const& cmd);

        DWORD get_exit_code() const noexcept;

    private:
        DWORD _exit_code;

    private:
        SHELLEXECUTEINFO make_shell_execute_info(command const& cmd);
    };
}

#endif