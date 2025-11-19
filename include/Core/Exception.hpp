
#pragma once

    #include <iostream>
    #include <exception>

namespace GGL
{

class Exception : std::exception
{
    public:
        explicit Exception(const std::string msg) : _msg(msg) {}

        const char *what() const noexcept override
        {
            return _msg.c_str();
        }

        class CurlPerform;
        class CurlResponseCode;

    private:
        std::string _msg;
};

} // namespace GGL
