
#pragma once

#include <fstream>
#include "Function.hpp"

namespace GGL
{
    #if defined(_WIN32)
        #define FOLDER_SEPARATOR        '\\'
    #else
        #define FOLDER_SEPARATOR        '/'
    #endif
    #define __FILENAME__        (strrchr(__FILE__, FOLDER_SEPARATOR) ? strrchr(__FILE__, FOLDER_SEPARATOR) + 1 : __FILE__)

    #define DEBUG_SETTING_FILE      0b0001
    #define DEBUG_SETTING_LINE      0b0010
    #define DEBUG_SETTING_FUNC      0b0100

    #define DEBUG_LOG_OUTPUT        "log/output.log"

class Debug
{
    public:
        #if defined(GGL_DEBUG)
            Debug(std::ostream &flux, std::string prefix, Color color, char settings = 0);
        #else
            Debug(std::string prefix, char settings = 0);
        #endif
        ~Debug();

        void addSetting(char value);
        void removeSetting(char value);

        Debug &printHeader(const char *file, int line, const char *func);
        Debug &operator()(const char *file, int line, const char *func);

        Debug &print(bool value);
        Debug &print(int8_t value);
        Debug &print(int16_t value);
        Debug &print(int32_t value);
        Debug &print(int64_t value);
        Debug &print(uint8_t value);
        Debug &print(uint16_t value);
        Debug &print(uint32_t value);
        Debug &print(uint64_t value);
        Debug &print(float value);
        Debug &print(double value);
        Debug &print(long double value);
        Debug &print(const char *str);
        Debug &print(const std::string str);
        Debug &print(const void *ptr);
        Debug &print(std::nullptr_t);
        Debug &flush();
        Debug &end();

        Debug &operator<<(bool value);
        Debug &operator<<(int8_t value);
        Debug &operator<<(int16_t value);
        Debug &operator<<(int32_t value);
        Debug &operator<<(int64_t value);
        Debug &operator<<(uint8_t value);
        Debug &operator<<(uint16_t value);
        Debug &operator<<(uint32_t value);
        Debug &operator<<(uint64_t value);
        Debug &operator<<(float value);
        Debug &operator<<(double value);
        Debug &operator<<(long double value);
        Debug &operator<<(const char *str);
        Debug &operator<<(const std::string str);
        Debug &operator<<(const void *ptr);
        Debug &operator<<(std::nullptr_t);
        Debug &operator<<(Debug &(*func)(Debug &));

    private:
        std::string getHeader(const char *file, int line, const char *func);

        #if defined(GGL_DEBUG)
            std::ostream &_flux;
            Color _color;
        #else
            std::ofstream _flux;
        #endif

        std::string _prefix;
        char _settings;
};

Debug &flush(Debug &debug);
Debug &end(Debug &debug);

extern "C++" Debug Log;
extern "C++" Debug Warning;
extern "C++" Debug Error;

#define Log()               GGL::Log(__FILENAME__, __LINE__, __func__)
#define Warning()           GGL::Warning(__FILENAME__, __LINE__, __func__)
#define Error()             GGL::Error(__FILENAME__, __LINE__, __func__)

} // namespace GGL
