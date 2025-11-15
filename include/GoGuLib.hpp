
#pragma once

#include "Random.hpp"
#include "Singleton.hpp"
#include "Exception.hpp"

namespace GGL
{

    #define DATE_FORMAT_DD_MM_YYYY      "dd/mm/yyyy"

// String
std::string getTimeFormat(std::string format);
std::string stringToUpper(std::string str);
std::string stringToLower(std::string str);
std::string getFullPath(std::string path);;

// Process
void createProcess(std::string path);

// Temp
std::string getTempDir();

} // namespace GGL

/*

BiMap
Debug

*/
