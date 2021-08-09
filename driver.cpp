#include "driver.hpp"
#include <algorithm>
#include <boost/math/constants/constants.hpp>
#include <fstream>
#include <vector>

namespace ccalc
{
    namespace mc = boost::math::constants;

    // class unknown_identifier
    unknown_identifier::unknown_identifier(const std::string& desc) : runtime_error(desc) {}
    unknown_identifier::unknown_identifier(const char* desc) : runtime_error(desc) {}

    // class Driver
    Driver::~Driver() {
        delete parser;
        parser = nullptr;
        delete scanner;
        scanner = nullptr;
    }

    void Driver::parse(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            exit(EXIT_FAILURE);
        }
        parse_helper(file);
    }

    void Driver::parse(std::istream& is) {
        if (is && !is.eof()) {
            parse_helper(is);
        }
    }

    void Driver::parse_helper(std::istream& stream) {
        delete scanner;
        try {
            scanner = new ccalc::Scanner(&stream);
        } catch (const std::bad_alloc& ba) {
            std::cerr << "Failed to allocate scanner: (" << ba.what() << "), exiting!!\n";
            exit(EXIT_FAILURE);
        }

        delete parser;
        try {
            parser = new ccalc::Parser(*scanner, *this);
        } catch (const std::bad_alloc& ba) {
            std::cerr << "Failed to allocate parser: (" << ba.what() << "), exiting!!\n";
            exit(EXIT_FAILURE);
        }

        if (driverMode == Mode::eval) {
            if (parser->parse() != 0) {
                std::cerr << "Parse failed!\n";
            }
        } else {
            const std::string prompt = driverMode == Mode::interactive ? ">> " : "";
            std::string str;
            while (scanner->good()) {
                std::cout << prompt;
                parser->parse();
                errorFlag = false;
            }
        }
    }

    void Driver::setMode(Mode m) {
        driverMode = m;
    }

    void Driver::setErrorFlag(bool err) {
        errorFlag = err;
    }

    bool Driver::getErrorFlag() const {
        return errorFlag;
    }

    void Driver::addVariable(const std::string& name, Float value) {
        variables[name] = value;
    }

    Float Driver::getVariable(const std::string& name) const {
        try {
            const auto p = predefinedVariables.find(name);
            return p != predefinedVariables.end() ? p->second : variables.at(name);
        } catch (const std::out_of_range& e) {
            throw unknown_identifier("Variable \"" + name + "\" does not exist.");
        }
    }

    Float Driver::call(const std::string& name, const std::vector<Float>& args) const {
        try {
            return functions.at(name)(args);
        } catch (const std::out_of_range& e) {
            throw unknown_identifier("\"" + name + "\" is not a function.");
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
        {"tan", builtin::tan}
    };
    // clang-format on

    // Definition of built-in functions
    namespace builtin
    {
        Float abs(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return mp::abs(args[0]);
        }

        Float sqrt(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return mp::sqrt(args[0]);
        }

        Float max(const std::vector<Float>& args) {
            if (args.size() < 2)
                throw std::invalid_argument("at least 2 arguments.");
            return *std::max_element(args.begin(), args.end());
        }

        Float min(const std::vector<Float>& args) {
            if (args.size() < 2)
                throw std::invalid_argument("at least 2 arguments.");
            return *std::min_element(args.begin(), args.end());
        }

        Float sin(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return mp::sin(args[0]);
        }

        Float cos(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return mp::cos(args[0]);
        }

        Float tan(const std::vector<Float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return mp::tan(args[0]);
        }
    } // namespace builtin

} // namespace ccalc
