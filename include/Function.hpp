
#pragma once

#include <iostream>

namespace GGL
{

    #define DATE_FORMAT_DD_MM_YYYY      "dd/mm/yyyy"

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

// Temp
std::string getTempDir();

} // namespace GGL
