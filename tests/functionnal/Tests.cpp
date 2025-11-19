
#include "GoGuLib.hpp"

#define GNCAPP_NAME         "GamenChillApp"
#define GNCAPP_VERSION      "v3.2.0"
#define GNCAPP_TARGET       "GamenChillApp_WIN32.zip"
#define GNCAPP_GITHUB_URL   "https://api.github.com/repos/Game-N-Chill/GamenChillApp/releases/latest"

int main(int ac, char **av)
{
    #if defined(_WIN32)
    GGL::setTerminalColor();
    #endif

    GGL::Updater updater(GNCAPP_NAME, GNCAPP_VERSION, GNCAPP_TARGET);

    updater.save("assets");
    updater.save("data");
    updater.save("template");
    updater.save("themes");

    if (updater(GNCAPP_GITHUB_URL) == EXIT_FAILURE) {
        system("pause");
        return EXIT_FAILURE;
    }

    GGL::createProcess(GGL::getFullPath("GamenChillApp.exe"));
    return EXIT_SUCCESS;
}
