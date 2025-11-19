
#pragma once

#include <iostream>
#include <vector>

namespace GGL
{

    #define DATE_FORMAT_DD_MM_YYYY      "%Y_%m_%d"
    #define DATE_FORMAT_HH_MM_SS        "%H_%M_%S"
    #define DATE_FORMAT_COMPLET         "%Y_%m_%d__%H_%M_%S"

enum Color {
    NONE = 0,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37
};

// String
std::string getColor(Color color);
std::string getTimeFormat(std::string format);
std::string stringToUpper(std::string str);
std::string stringToLower(std::string str);
std::string getFullPath(std::string path);;

// Process
void createProcess(std::string path);
#if defined(_WIN32)
void setTerminalColor();
#endif

// Temp
std::string getTempDir();

} // namespace GGL
