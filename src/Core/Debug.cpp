
#include "Core/Debug.hpp"
#include <vector>
#include <string>

namespace GGL
{

#if defined(GGL_DEBUG)

Debug Log =     Debug(std::cout, "Info",    Color::BLUE,    DEBUG_SETTING_FILE | DEBUG_SETTING_LINE | DEBUG_SETTING_FUNC);
Debug Warning = Debug(std::cout, "Warning", Color::YELLOW,  DEBUG_SETTING_FILE | DEBUG_SETTING_LINE | DEBUG_SETTING_FUNC);
Debug Error =   Debug(std::cerr, "Error",   Color::RED,     DEBUG_SETTING_FILE | DEBUG_SETTING_LINE | DEBUG_SETTING_FUNC);

Debug::Debug(std::ostream &flux, std::string prefix, Color color, char settings) :
    _flux(flux),
    _prefix(prefix),
    _color(color)
{
    addSetting(settings);
}

#else

Debug Log =     Debug("Info",    DEBUG_SETTING_FILE | DEBUG_SETTING_LINE | DEBUG_SETTING_FUNC);
Debug Warning = Debug("Warning", DEBUG_SETTING_FILE | DEBUG_SETTING_LINE | DEBUG_SETTING_FUNC);
Debug Error =   Debug("Error",   DEBUG_SETTING_FILE | DEBUG_SETTING_LINE | DEBUG_SETTING_FUNC);

Debug::Debug(std::string prefix, char settings) :
    _prefix(prefix),
    _flux(DEBUG_LOG_OUTPUT)
{
}

#endif

Debug::~Debug()
{
}

static void add(char &toSave, char toCheck, char setting)
{
    if ((toCheck & setting) == setting)
        toSave |= setting;
}

void Debug::addSetting(char value)
{
    add(this->_settings, value, DEBUG_SETTING_FILE);
    add(this->_settings, value, DEBUG_SETTING_LINE);
    add(this->_settings, value, DEBUG_SETTING_FUNC);
}

static void remove(char &toSave, char toCheck, char setting)
{
    if ((toCheck & setting) == setting)
        toSave &= ~setting;
}

void Debug::removeSetting(char value)
{
    remove(this->_settings, value, DEBUG_SETTING_FILE);
    remove(this->_settings, value, DEBUG_SETTING_LINE);
    remove(this->_settings, value, DEBUG_SETTING_FUNC);
}

std::string Debug::getHeader(const char *file, int line, const char *func)
{
    #if defined(GGL_DEBUG)
        std::string header = '[' + getColor(this->_color) + this->_prefix + getColor(Color::NONE) + ']';
    #else
        std::string header = '[' + this->_prefix + ']';
    #endif

    if (this->_settings == 0) {
        header = " - ";
        return header;
    }

    std::vector<std::string> vec;
    if ((this->_settings & DEBUG_SETTING_FILE) == DEBUG_SETTING_FILE)
        vec.push_back(file);
    if ((this->_settings & DEBUG_SETTING_LINE) == DEBUG_SETTING_LINE)
        vec.push_back(std::to_string(line));
    if ((this->_settings & DEBUG_SETTING_FUNC) == DEBUG_SETTING_FUNC)
        vec.push_back(func);

    header += " (";
    for (size_t i = 0; i < vec.size(); i++) {
        header += vec[i];
        if (i < vec.size() - 1) {
            header += ':';
        }
    }
    header += ") - ";

    return header;
}

Debug &Debug::printHeader(const char *file, int line, const char *func)
{
    this->_flux << getHeader(file, line, func);
    return *this;
}

Debug &Debug::operator()(const char *file, int line, const char *func)
{
    return printHeader(file, line, func);
}

Debug &Debug::print(bool value)
{
    this->_flux << (value ? "true" : "false");
    return *this;
}

Debug &Debug::print(int8_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(int16_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(int32_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(int64_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(uint8_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(uint16_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(uint32_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(uint64_t value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(float value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(double value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(long double value)
{
    this->_flux << value;
    return *this;
}

Debug &Debug::print(const char *str)
{
    this->_flux << str;
    return *this;
}

Debug &Debug::print(const std::string str)
{
    this->_flux << str;
    return *this;
}

Debug &Debug::print(const void *ptr)
{
    this->_flux << ptr;
    return *this;
}

Debug &Debug::print(std::nullptr_t)
{
    this->_flux << "(nullptr)";
    return *this;
}

Debug &Debug::flush()
{
    this->_flux.flush();
    return *this;
}

Debug &Debug::end()
{
    this->_flux << std::endl;
    return *this;
}

Debug &Debug::operator<<(bool value)
{
    return print(value);
}

Debug &Debug::operator<<(int8_t value)
{
    return print(value);
}

Debug &Debug::operator<<(int16_t value)
{
    return print(value);
}

Debug &Debug::operator<<(int32_t value)
{
    return print(value);
}

Debug &Debug::operator<<(int64_t value)
{
    return print(value);
}

Debug &Debug::operator<<(uint8_t value)
{
    return print(value);
}

Debug &Debug::operator<<(uint16_t value)
{
    return print(value);
}

Debug &Debug::operator<<(uint32_t value)
{
    return print(value);
}

Debug &Debug::operator<<(uint64_t value)
{
    return print(value);
}

Debug &Debug::operator<<(float value)
{
    return print(value);
}

Debug &Debug::operator<<(double value)
{
    return print(value);
}

Debug &Debug::operator<<(long double value)
{
    return print(value);
}

Debug &Debug::operator<<(const char *str)
{
    return print(str);
}

Debug &Debug::operator<<(const std::string str)
{
    return print(str);
}

Debug &Debug::operator<<(const void *ptr)
{
    return print(ptr);
}

Debug &Debug::operator<<(std::nullptr_t)
{
    return print(nullptr);
}

Debug &Debug::operator<<(Debug &(*func)(Debug &))
{
    return func(*this);
}

Debug &flush(Debug &debug)
{
    return debug.flush();
}

Debug &end(Debug &debug)
{
    return debug.end();
}

} // namespace GGL
