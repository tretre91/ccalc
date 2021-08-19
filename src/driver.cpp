#include "driver.hpp"
#include <algorithm>
#include <boost/math/constants/constants.hpp>
#include <fstream>

namespace ccalc
{
    namespace mc = boost::math::constants;

    void Driver::parse(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open file \"" << filename << "\"\n";
            exit(EXIT_FAILURE);
        }
        loc.initialize(&filename);
        parse(file);
        loc.initialize();
    }

    void Driver::endParse() {
        shouldEnd = true;
    }

    void Driver::setMode(Mode m) {
        driverMode = m;
    }

    Mode Driver::getMode() const {
        return driverMode;
    }

    ccalc::location& Driver::getLocation() {
        return loc;
    }

    void ccalc::Driver::setLastResult(const Float& f) {
        lastResult = f;
    }

    Float Driver::getLastResult() const {
        return lastResult;
    }

    void Driver::addVariable(const std::string& name, Float value) {
        variables[name] = value;
    }

    Float Driver::getVariable(const std::string& name) const {
        try {
            const auto p = predefinedVariables.find(name);
            return p != predefinedVariables.end() ? p->second : variables.at(name);
        } catch (const std::out_of_range& e) {
            throw UndefinedIdentifier("Variable \"" + name + "\" does not exist.");
        }
    }

    Float Driver::call(const std::string& name, const std::vector<Float>& args) const {
        try {
            return functions.at(name)(args);
        } catch (const std::out_of_range& e) {
            throw UndefinedIdentifier("\"" + name + "\" is not a function.");
        }
    }

    void Driver::callSysFunction(const std::string& name, const std::vector<Float>& args) const {
        try {
            sysFunctions.at(name)(args);
        } catch (const std::out_of_range& e) {
            throw UndefinedIdentifier("\"" + name + "\" is not a system function.");
        }
    }

    // clang-format off
    const std::unordered_map<std::string, Float> Driver::predefinedVariables = {
        {"pi", mc::pi<Float>()},
        {"e", mc::e<Float>()},
        {"degree", mc::degree<Float>()},
        {"radian", mc::radian<Float>()}
    };

    const std::unordered_map<std::string, std::function<Float(const std::vector<Float>&)>> Driver::functions = {
        {"abs", builtin::abs},
        {"sqrt", builtin::sqrt},
        {"max", builtin::max},
        {"min", builtin::min},
        {"sin", builtin::sin},
        {"cos", builtin::cos},
        {"tan", builtin::tan},
    };

    const std::unordered_map<std::string, std::function<void(const std::vector<Float>&)>> Driver::sysFunctions = {
        {"setPrecision", sys::setPrecision}
    };
    // clang-format on

    // Definition of built-in functions
    namespace builtin
    {
        Float abs(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw InvalidArgument("Function \"abs\" takes exactly 1 argument.");
            return mp::abs(args[0]);
        }

        Float sqrt(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw InvalidArgument("Function \"sqrt\" takes exactly 1 argument.");
            return mp::sqrt(args[0]);
        }

        Float max(const std::vector<Float>& args) {
            if (args.size() < 2)
                throw InvalidArgument("Function \"max\" takes at least 2 arguments.");
            return *std::max_element(args.begin(), args.end());
        }

        Float min(const std::vector<Float>& args) {
            if (args.size() < 2)
                throw InvalidArgument("Function \"min\" takes at least 2 arguments.");
            return *std::min_element(args.begin(), args.end());
        }

        Float sin(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw InvalidArgument("Function \"sin\" takes exactly 1 argument.");
            const ccalc::Float res = mp::sin(args[0]);
            return mp::abs(res) > std::numeric_limits<ccalc::Float>::epsilon() ? res : ccalc::Float(0);
        }

        Float cos(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw InvalidArgument("Function \"cos\" takes exactly 1 argument.");
            const ccalc::Float res = mp::cos(args[0]);
            return mp::abs(res) > std::numeric_limits<ccalc::Float>::epsilon() ? res : ccalc::Float(0);
        }

        Float tan(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw InvalidArgument("Function \"tan\" takes exactly 1 argument.");
            // return mp::tan(args[0]);
            return sin(args) / cos(args);
        }
    } // namespace builtin

    namespace sys
    {
        void setPrecision(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw InvalidArgument("Function \"setPrecision\" takes exactly 1 argument.");
            const int p = static_cast<int>(mp::round(args[0]));
            if (p < 0)
                throw InvalidArgument("setPrecision expects a positive argument or 0 for the maximum number of significant digits");
            std::cout.precision(p);
        }
    } // namespace sys
} // namespace ccalc
