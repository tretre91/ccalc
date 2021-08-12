#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

namespace ccalc
{
    /**
     * @brief Base class for ccalc exceptions
     */
    class Exception : public std::runtime_error
    {
    public:
        Exception(const char* desc) : runtime_error(desc) {}
        Exception(const std::string& desc) : runtime_error(desc) {}
    };

    /**
     * @brief Exception thrown when an identifier (function or variable name) is undefined
     */
    class UndefinedIdentifier : public Exception
    {
    public:
        UndefinedIdentifier(const char* desc) : Exception(desc) {}
        UndefinedIdentifier(const std::string& desc) : Exception(desc) {}
    };

    /**
     * @brief Exception thrown when an argument to a function call is invalid
     */
    class InvalidArgument : public Exception
    {
    public:
        InvalidArgument(const char* desc) : Exception(desc) {}
        InvalidArgument(const std::string& desc) : Exception(desc) {}
    };
} // namespace ccalc

#endif // !EXCEPTIONS_HPP
