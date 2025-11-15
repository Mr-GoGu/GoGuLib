
#include "GoGuLib.hpp"

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
        MessageBoxA(nullptr, (std::string("Can't find ") + path).c_str(), "Error", MB_OK | MB_ICONERROR);
    }
}

#else

void createProcess(std::string path)
{
}

#endif

}
