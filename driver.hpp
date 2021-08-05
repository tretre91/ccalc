#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <cmath>
#include <cstddef>
#include <functional>
#include <istream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "calc.tab.hh"
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

        void addVariable(const std::string& name, float value);
        float getVariable(const std::string& name) const;
        float call(const std::string& name, const std::vector<float>& args) const;

    private:
        ccalc::Parser* parser = nullptr;
        ccalc::Scanner* scanner = nullptr;
        ccalc::Mode driverMode = Mode::interactive;
        bool errorFlag = false;
        std::unordered_map<std::string, float> variables = {{"pi", 3.141592653589793f}, {"e", 2.718281828459045f}};
        const static std::unordered_map<std::string, std::function<float(const std::vector<float>&)>> functions;

        void parse_helper(std::istream& stream);
    };

    namespace builtin
    {
        float abs(const std::vector<float>& args);
        float sqrt(const std::vector<float>& args);
        float max(const std::vector<float>& args);
        float min(const std::vector<float>& args);
        float sin(const std::vector<float>& args);
        float cos(const std::vector<float>& args);
        float tan(const std::vector<float>& args);
    } // namespace builtin
} // namespace ccalc

#endif // !DRIVER_HPP
