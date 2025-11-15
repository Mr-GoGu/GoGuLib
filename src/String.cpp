
#include "GoGuLib.hpp"
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
namespace GGL
{

std::string getTimeFormat(std::string format)
{
    std::time_t now = std::time(nullptr);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now), format.c_str());
    return oss.str();
}

std::string stringToUpper(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](uint8_t c) {
        return std::toupper(c);
    });
    return str;
}

std::string stringToLower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](uint8_t c) {
        return std::tolower(c);
    });
    return str;
}

std::string getFullPath(std::string path)
{
    std::string fullPath = std::filesystem::current_path().string() + "/" + std::string(path);
    std::replace(fullPath.begin(), fullPath.end(), '\\', '/');
    return fullPath;
}

}
