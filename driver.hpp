#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <cstddef>
#include <functional>
#include <istream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "calc.tab.hh"
#include "common.hpp"
#include "scanner.hpp"

namespace ccalc
{
    enum class Mode
    {
        interactive,
        file,
        eval
    };

    class unknown_identifier : public std::runtime_error
    {
    public:
        unknown_identifier(const std::string& desc);
        unknown_identifier(const char* desc);
    };

    class Driver
    {
    public:
        Driver() = default;
        virtual ~Driver();

        void parse(const std::string& filename);
        void parse(std::istream& is);

        void setMode(Mode m);
        void setErrorFlag(bool err);
        bool getErrorFlag() const;

        void addVariable(const std::string& name, Float value);
        Float getVariable(const std::string& name) const;
        Float call(const std::string& name, const std::vector<Float>& args) const;

    private:
        ccalc::Parser* parser = nullptr;
        ccalc::Scanner* scanner = nullptr;
        ccalc::Mode driverMode = Mode::interactive;
        bool errorFlag = false;
        std::unordered_map<std::string, Float> variables;
        const static std::unordered_map<std::string, Float> predefinedVariables;
        const static std::unordered_map<std::string, std::function<Float(const std::vector<Float>&)>> functions;

        void parse_helper(std::istream& stream);
    };

    namespace builtin
    {
        Float abs(const std::vector<Float>& args);
        Float sqrt(const std::vector<Float>& args);
        Float max(const std::vector<Float>& args);
        Float min(const std::vector<Float>& args);
        Float sin(const std::vector<Float>& args);
        Float cos(const std::vector<Float>& args);
        Float tan(const std::vector<Float>& args);
    } // namespace builtin
} // namespace ccalc

#endif // !DRIVER_HPP
