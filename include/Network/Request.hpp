
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>

#include "Core/Exception.hpp"

namespace GGL
{

#define MOZILLA_USER_AGENT          "Mozilla/5.0"

class Request
{
    public:
        typedef size_t (*Func)(void *, size_t, size_t, void *);

        static size_t WriteToString(void *contents, size_t size, size_t nmemb, void *output);
        static size_t WriteToFile(void *contents, size_t size, size_t nmemb, void *output);

        Request();
        ~Request();

        std::string Get(std::string url);
        void Download(std::string url, std::string path);

        void SetOpt(CURLoption key, const char *value);
        void SetOpt(CURLoption key, std::string value);
        void SetOpt(CURLoption key, int value);
        void SetHeader(std::vector<std::string> vec);
        void ResetOpt();

    private:
        CURL *_curl;

        void SetFetchOpt(std::string url, Func func, void *data);
};


class Exception::CurlPerform : public Exception
{
    public:
        explicit CurlPerform(const CURLcode errorCode) : Exception(std::string("curl failed to perform (") + curl_easy_strerror(errorCode) + ")") {}
};

class Exception::CurlResponseCode : public Exception
{
    public:
        explicit CurlResponseCode(const long errorCode) : Exception("failed to fetch content, error code: " + std::to_string(errorCode)) {}
};

} // namespace GGL
