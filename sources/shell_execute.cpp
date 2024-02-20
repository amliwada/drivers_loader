#include <drivers_loader/shell_execute.hpp>
#include <drivers_loader/shell_execute_exception.hpp>

void drivers_loader::shell_execute::runas(command const& cmd)
{
    auto shell_execute_info{ this->make_shell_execute_info(cmd) };

    shell_execute_info.lpVerb = L"runas";

    if (ShellExecuteEx(&shell_execute_info))
    {
        WaitForSingleObject(shell_execute_info.hProcess, INFINITE);
        GetExitCodeProcess(shell_execute_info.hProcess, &this->_exit_code);
    }
    else
    {
        this->_exit_code = GetLastError();
        throw shell_execute_exception{ this->_exit_code };
    }
}

SHELLEXECUTEINFO drivers_loader::shell_execute::make_shell_execute_info(command const& cmd)
{
    SHELLEXECUTEINFO shell_execute_info;

    shell_execute_info.cbSize = sizeof(SHELLEXECUTEINFO);
    shell_execute_info.fMask = SEE_MASK_NOCLOSEPROCESS;
    shell_execute_info.hwnd = NULL;
    shell_execute_info.lpVerb = NULL;
    shell_execute_info.lpFile = (LPTSTR)cmd.get_name().utf16();
    shell_execute_info.lpParameters = (LPTSTR)cmd.get_parameters_string().utf16();
    shell_execute_info.lpDirectory = NULL;
    shell_execute_info.nShow = SW_MINIMIZE;
    shell_execute_info.hInstApp = NULL;

    return shell_execute_info;
}

DWORD drivers_loader::shell_execute::get_exit_code() const noexcept
{
    return this->_exit_code;
}