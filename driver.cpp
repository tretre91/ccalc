#include "driver.hpp"
#include <algorithm>
#include <fstream>
#include <vector>

namespace ccalc
{
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

    void Driver::addVariable(const std::string& name, float value) {
        variables[name] = value;
    }

    float Driver::getVariable(const std::string& name) const {
        try {
            return variables.at(name);
        } catch (const std::out_of_range& e) {
            throw unknown_identifier("Variable \"" + name + "\" does not exist.");
        }
    }

    float Driver::call(const std::string& name, const std::vector<float>& args) const {
        try {
            return functions.at(name)(args);
        } catch (const std::out_of_range& e) {
            throw unknown_identifier("\"" + name + "\" is not a function.");
        }
    }

    // clang-format off
    const std::unordered_map<std::string, std::function<float(const std::vector<float>&)>> Driver::functions = {
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
        float abs(const std::vector<float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return std::fabs(args[0]);
        }

        float sqrt(const std::vector<float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return std::sqrtf(args[0]);
        }

        float max(const std::vector<float>& args) {
            if (args.size() < 2)
                throw std::invalid_argument("at least 2 arguments.");
            return *std::max_element(args.begin(), args.end());
        }

        float min(const std::vector<float>& args) {
            if (args.size() < 2)
                throw std::invalid_argument("at least 2 arguments.");
            return *std::min_element(args.begin(), args.end());
        }

        float sin(const std::vector<float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return std::sinf(args[0]);
        }

        float cos(const std::vector<float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return std::cosf(args[0]);
        }

        float tan(const std::vector<float>& args) {
            if (args.size() != 1)
                throw std::invalid_argument("exactly 1 argument.");
            return std::tanf(args[0]);
        }
    } // namespace builtin

} // namespace ccalc
