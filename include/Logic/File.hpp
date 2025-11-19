
#pragma once

#include <vector>
#include <fstream>
#include <minizip/unzip.h>

namespace GGL
{

std::vector<uint8_t> readFileToMemory(std::string path);

void extractZipFile(std::string path);

} // namespace GGL
