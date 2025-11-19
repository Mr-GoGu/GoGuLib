
#include "Network/Request.hpp"
#include "Core/Exception.hpp"
#include <sstream>
#include <fstream>

namespace GGL
{

//  STATIC
// *****************************************************************************

size_t Request::WriteToString(void *contents, size_t size, size_t nmemb, void *output)
{
    std::string *str = static_cast<std::string*>(output);
    size_t totalSize = size * nmemb;
    str->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

size_t Request::WriteToFile(void *contents, size_t size, size_t nmemb, void *output)
{
    std::ofstream *file = static_cast<std::ofstream *>(output);
    size_t totalSize = size * nmemb;
    file->write(static_cast<char *>(contents), totalSize);
    return totalSize;
}

//  CLASS
// *****************************************************************************

Request::Request()
{
    this->_curl = curl_easy_init();
    if (!this->_curl) {
        throw Exception("failed to initialize curl");
    }

    curl_easy_setopt(this->_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(this->_curl, CURLOPT_MAXREDIRS, 10L);
    curl_easy_setopt(this->_curl, CURLOPT_USERAGENT, MOZILLA_USER_AGENT);
    curl_easy_setopt(this->_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(this->_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(this->_curl, CURLOPT_CONNECTTIMEOUT, 15L);
    curl_easy_setopt(this->_curl, CURLOPT_TIMEOUT, 0L);
}

Request::~Request()
{
    curl_easy_cleanup(this->_curl);
}


void Request::SetFetchOpt(std::string url, Func func, void *data)
{
    curl_easy_setopt(this->_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->_curl, CURLOPT_WRITEFUNCTION, func);
    curl_easy_setopt(this->_curl, CURLOPT_WRITEDATA, data);
    #if _DEBUG
        curl_easy_setopt(this->_curl, CURLOPT_VERBOSE, 1L);
    #endif

    CURLcode responseCode = curl_easy_perform(this->_curl);
    if (responseCode != CURLE_OK) {
        throw Exception::CurlPerform(responseCode);
    }

    long code = 0;
    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &code);
    if (code != 200) {
        throw Exception::CurlResponseCode(code);
    }
}

void Request::SetOpt(CURLoption key, const char *value)
{
    curl_easy_setopt(this->_curl, key, value);
}

void Request::SetOpt(CURLoption key, std::string value)
{
    curl_easy_setopt(this->_curl, key, value.c_str());
}

void Request::SetOpt(CURLoption key, int value)
{
    curl_easy_setopt(this->_curl, key, value);
}

void Request::SetHeader(std::vector<std::string> vec)
{
    struct curl_slist *headers = NULL;
    for (auto str : vec) {
        headers = curl_slist_append(headers, str.c_str());
    }
    curl_easy_setopt(this->_curl, CURLOPT_HTTPHEADER, headers);
}

void Request::ResetOpt()
{
    curl_easy_reset(this->_curl);
}

std::string Request::Get(std::string url)
{
    std::string data;
    this->SetFetchOpt(url, &Request::WriteToString, &data);
    return data;
}

void Request::Download(std::string url, std::string path)
{
    std::ofstream file(path, std::ios::binary);
    this->SetFetchOpt(url, &Request::WriteToFile, &file);
    file.close();
}


}
