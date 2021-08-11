#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

namespace ccalc
{
    class Exception : public std::runtime_error
    {
    public:
        Exception(const char* desc) : runtime_error(desc) {}
        Exception(const std::string& desc) : runtime_error(desc) {}
    };

    class UnknownIdentifier : public Exception
    {
    public:
        UnknownIdentifier(const char* desc) : Exception(desc) {}
        UnknownIdentifier(const std::string& desc) : Exception(desc) {}
    };

    class InvalidArgument : public Exception
    {
    public:
        InvalidArgument(const char* desc) : Exception(desc) {}
        InvalidArgument(const std::string& desc) : Exception(desc) {}
    };
} // namespace ccalc

#endif // !EXCEPTIONS_HPP
