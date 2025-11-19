
#include "Logic/File.hpp"
#include "Core/Exception.hpp"
#include "Core/Debug.hpp"
#include <filesystem>

namespace fs = std::filesystem;
namespace GGL
{

std::vector<uint8_t> readFileToMemory(std::string path)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw Exception("Cannot open zip file " + path);
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(fileSize);
    if (!file.read((char *)buffer.data(), fileSize)) {
        throw Exception("Cannot read zip file " + path);
    }

    return buffer;
}


void extractZipFile(std::string path)
{
    unzFile zip = unzOpen(path.c_str());

    if (zip == nullptr) {
        throw Exception("failed to open zip file: " + path);
    }

    if (unzGoToFirstFile(zip) != UNZ_OK) {
        throw Exception("failed to seek first file of zip file: " + path);
    }

    do {
        // Get current file name
        char bufferName[256];
        if (unzGetCurrentFileInfo(zip, nullptr, bufferName, sizeof(bufferName), nullptr, 0, nullptr, 0) != UNZ_OK) {
            Warning() << "could not get current file info, skipping..." << end;
            continue;
        }
        std::string fileName(bufferName);

        // Create directories of the extracted file if they don't exists
        size_t hasDir = fileName.find_last_of('/');
        if (hasDir != std::string::npos) {
            std::string dir = fileName.substr(0, hasDir);
            if (!fs::exists(dir)) {
                fs::create_directories(dir);
            }
        }

        // Opening current file
        if (unzOpenCurrentFile(zip)) {
            Warning() << "could not open current file " << fileName << ", skipping..." << end;
            continue;
        }
        std::ofstream file(fileName, std::ios::binary);

        char buffer[4096];
        int bytes;
        while ((bytes = unzReadCurrentFile(zip, buffer, sizeof(buffer))) > 0) {
            file.write(buffer, bytes);
        }

        file.close();
        unzCloseCurrentFile(zip);

        Log() << "Successfully extracted " << fileName << end;
    } while (unzGoToNextFile(zip) == UNZ_OK);

    unzClose(zip);
}

} // namespace GGL
