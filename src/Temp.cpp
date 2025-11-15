
#include "GoGuLib.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace GGL
{

std::string getTempDir()
{
    std::string path = std::getenv("LOCALAPPDATA");
    if (path.empty()) {
        throw std::runtime_error("can't find envrionment variable LOCALAPPDATA");
    }

    if (!fs::exists(path)) {
        throw std::runtime_error(path + " path doesn't exist");
    }

    std::replace(path.begin(), path.end(), '\\', '/');
    return path;
}

}
