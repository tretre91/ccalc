#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <cstddef>
#include <functional>
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

#include "common.hpp"
#include "exceptions.hpp"
#include "parser.hh"
#undef YY_DECL
#define YY_DECL ccalc::Parser::symbol_type yylex(ccalc::Driver& driver)
YY_DECL;

namespace ccalc
{
    enum class Mode
    {
        interactive,
        file,
        eval
    };

    class Driver
    {
    public:
        Driver() = default;

        void parse(const std::string& filename);
        void parse(std::istream& stream);
        void endParse();

        void setMode(Mode m);
        ccalc::location& getLocation();

        void addVariable(const std::string& name, Float value);
        Float getVariable(const std::string& name) const;
        Float call(const std::string& name, const std::vector<Float>& args) const;
        void callSysFunction(const std::string& name, const std::vector<Float>& args) const;

    private:
        ccalc::location loc;
        ccalc::Mode driverMode = Mode::interactive;
        std::unordered_map<std::string, Float> variables;
        bool shouldEnd = false;

        const static std::unordered_map<std::string, Float> predefinedVariables;
        const static std::unordered_map<std::string, std::function<Float(const std::vector<Float>&)>> functions;
        const static std::unordered_map<std::string, std::function<void(const std::vector<Float>&)>> sysFunctions;
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

    namespace sys
    {
        void setPrecision(const std::vector<Float>& args);
    } // namespace sys
} // namespace ccalc

#endif // !DRIVER_HPP
