
#pragma once

    #include <iostream>
    #include <exception>

namespace Oui
{

class Exception
{
    public:

        class IException : public std::exception
        {
            public:
                virtual const char *what() const noexcept override = 0;
        };

        class AException : IException
        {
            public:
                explicit AException(const std::string msg) : _msg(msg) {}

                const char *what() const noexcept override
                {
                    return _msg.c_str();
                }

            private:
                std::string _msg;
        };
};

} // namespace Oui
