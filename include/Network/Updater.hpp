#pragma once

#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Core/Exception.hpp"
#include "Network/Request.hpp"

namespace GGL
{

#define GITHUB_API_TAG                  "tag_name"
#define GITHUB_API_ASSETS               "assets"
#define GITHUB_API_ASSET_NAME           "name"
#define GITHUB_API_ASSET_URL            "browser_download_url"

#define UPDATER_DEFAULT_TEMP_DIR        "GoGuLib"
#define UPDATER_DEFAULT_SAVE_DIR        "save"

class Updater
{
    public:
        Updater(std::string appName, std::string version, std::string target);
        ~Updater();

        int execute();
        int execute(std::string url);
        int operator()();
        int operator()(std::string url);

        int fetchUpdate(std::string url);
        bool needsUpdate();

        void save(std::string data);
        void save(std::vector<std::string> data);

    private:
        void downloadUpdate();
        void saveApp();
        void clearApp();
        void installUpdate();
        void installSave();

        std::string _version;
        std::string _appName;
        std::string _target;

        Request _req;
        json _json;

        std::string _pathCurr;
        std::string _pathTemp;
        std::string _pathSave;
        std::string _pathFile;

        std::vector<std::string> _toSave;
};

} // namespace GGL
