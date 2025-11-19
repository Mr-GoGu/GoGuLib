
#include "Core/Function.hpp"
#include "Core/Debug.hpp"

namespace GGL
{

#if defined(_WIN32)
#include <Windows.h>

void createProcess(std::string path)
{
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;

    if (CreateProcessA(
        path.c_str(),           // Application name
        nullptr,                // Command line args
        nullptr,                // Process handle not inheritable
        nullptr,                // Thread handle not inheritable
        false,                  // Don't inherit handles
        CREATE_NEW_CONSOLE,     // New console window
        nullptr,                // Use parent's environment
        nullptr,                // Use parent's current directory
        &si,                    // Pointer to STARTUPINFO
        &pi)                    // Pointer to PROCESS_INFORMATION
    ) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        std::exit(EXIT_SUCCESS);
    } else {
        Error() << "Can't find " << path << end;
    }
}

void setTerminalColor()
{
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

#else

void createProcess(std::string path)
{
}

#endif

}
