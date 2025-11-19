
#include "Network/Updater.hpp"
#include "Core/Function.hpp"
#include "Core/Debug.hpp"
#include "Logic/File.hpp"
#include <filesystem>
#include <fstream>
#include <minizip/unzip.h>

namespace fs = std::filesystem;
namespace GGL
{

Updater::Updater(std::string appName, std::string version, std::string target)
{
    this->_appName = appName;
    this->_version = version;
    this->_target = target;

    this->_pathTemp = getTempDir() + '/' + appName + '/';
    this->_pathSave = this->_pathTemp + UPDATER_DEFAULT_SAVE_DIR + '/';
    if (!fs::exists(this->_pathTemp)) {
        fs::create_directory(this->_pathTemp);
    }
    if (!fs::exists(this->_pathSave)) {
        fs::create_directory(this->_pathSave);
    }

    this->_pathCurr = fs::current_path().string();
    std::replace(this->_pathCurr.begin(), this->_pathCurr.end(), '\\', '/');

    Log() << "pathTemp: " << _pathTemp << end;
    Log() << "pathSave: " << _pathSave << end;
    Log() << "pathCurr: " << _pathCurr << end;
}

Updater::~Updater()
{
}

int Updater::execute()
{
    try {
        downloadUpdate();
        Log() << "Succesfully downloaded update" << end;
        saveApp();
        Log() << "Succesfully saved app" << end;
        clearApp();
        Log() << "Succesfully cleared app" << end;
        installUpdate();
        Log() << "Succesfully installed update" << end;
        installSave();
        Log() << "Succesfully installed save" << end;
    } catch (const Exception &e) {
        Error() << e.what() << end;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int Updater::execute(std::string url)
{
    if (this->_json.empty()) {
        if (fetchUpdate(url) == EXIT_FAILURE) {
            Error() << "Failed to fetch update" << end;
            return EXIT_FAILURE;
        }
        Log() << "Succesfully fetch update" << end;
    } else {
        Warning() << "Updater json is not empty, a fetch has already been attempted" << end;
    }
    return execute();
}

int Updater::operator()()
{
    return execute();
}

int Updater::operator()(std::string url)
{
    return execute(url);
}


bool Updater::needsUpdate()
{
    if (this->_json.empty()) {
        return false;
    }
    return (this->_json[GITHUB_API_TAG] != this->_version);
}

int Updater::fetchUpdate(std::string url)
{
    try {
        std::string response = this->_req.Get(url);
        this->_json = json::parse(response);
    } catch (const Exception::CurlPerform &e) {
        Error() << e.what() << end;
        return EXIT_FAILURE;
    } catch (const Exception::CurlResponseCode &e) {
        Error() << e.what() << end;
        return EXIT_FAILURE;
    } catch (const Exception &e) {
        Error() << e.what() << end;
        return EXIT_FAILURE;
    } catch (const json::parse_error &e) {
        Error() << e.what() << end;
        return EXIT_FAILURE;
    } catch (const json::exception &e) {
        Error() << e.what() << end;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void Updater::downloadUpdate()
{
    Log() << "Update found, downloading latest version..." << end;

    for (json &release : this->_json[GITHUB_API_ASSETS]) {
        std::string name = release[GITHUB_API_ASSET_NAME].get<std::string>();
        std::string url = release[GITHUB_API_ASSET_URL].get<std::string>();
        if (name == this->_target) {
            this->_pathFile = this->_pathTemp + name;
            try {
                this->_req.Download(url, this->_pathFile);
            } catch (const Exception::CurlPerform &e) {
                Error() << "failed to download: " << e.what() << end;
            } catch (const Exception::CurlResponseCode &e) {
                Error() << "failed to download: " << e.what() << end;
            } catch (const Exception &e) {
                Error() << "failed to download: " << e.what() << end;
            }
            return;
        }
    }

    throw Exception(std::string("could not find target ") + this->_target);
}

void Updater::saveApp()
{
    Log() << "Saving data from current version..." << end;

    for (const auto &entry : std::filesystem::directory_iterator(this->_pathCurr)) {
        std::string data = entry.path().filename().string();

        if (std::find(this->_toSave.begin(), this->_toSave.end(), data) == this->_toSave.end())
            continue;

        fs::copy_options copyOptions = fs::copy_options::update_existing;
        if (entry.is_directory()) {
            copyOptions |= fs::copy_options::recursive;
        }

        fs::copy(data, this->_pathSave + data, copyOptions);
        Log() << "copied " << data << " into " << this->_pathSave << end;
    }
}

void Updater::clearApp()
{
    Log() << "Clearing current application..." << end;

    for (const auto &entry : std::filesystem::directory_iterator(this->_pathCurr)) {
        std::string path = entry.path().string();
        std::replace(path.begin(), path.end(), '\\', '/');

        try {
            if (entry.is_directory()) {
                fs::remove_all(path);
            } else {
                fs::remove(path);
            }
            Log() << "Successfully deleted " << path << end;
        } catch (const fs::filesystem_error& e) {
            Warning() << "can't delete " << path << ": " << e.what() << end;
        }
    }
}

void Updater::installUpdate()
{
    Log() << "Installing update..." << end;

    std::string fileName = _pathFile.substr(_pathFile.find_last_of('/'));

    fs::copy(this->_pathFile, this->_pathCurr + fileName);
    fs::remove(this->_pathFile);
    Log() << "moved " << this->_pathFile << " to " << this->_pathCurr + fileName << end;
    this->_pathFile = this->_pathCurr + fileName;

    Log() << "extracting " << this->_pathFile << end;
    extractZipFile(this->_pathFile);

    fs::remove(this->_pathFile);
}

void Updater::installSave()
{
    Log() << "Installing save..." << end;

    for (const auto &entry : std::filesystem::directory_iterator(this->_pathSave)) {
        std::string path = entry.path().string();
        std::replace(path.begin(), path.end(), '\\', '/');
        std::string name = path.substr(path.find_last_of('/'));

        fs::copy(path, this->_pathCurr + name, fs::copy_options::recursive | fs::copy_options::update_existing);
        fs::remove_all(path);

        Log() << "moved " << path << " to " << this->_pathCurr + name << end;
    }
}



void Updater::save(std::string data)
{
    this->_toSave.push_back(data);
}

void Updater::save(std::vector<std::string> data)
{
    for (auto &it : data) {
        save(it);
    }
}



}
