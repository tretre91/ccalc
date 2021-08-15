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
    /**
     * @brief Modes in which the driver operates
     * - interactive : the program runs in an interactive session
     * - file        : only the results are printed
     * - eval        : similar to file, except that only one line of input is processed
     * - test        : used for the tests, prints nothing
     */
    enum class Mode
    {
        interactive,
        file,
        eval,
        test
    };

    /**
     * @brief Class managing the core oprations of the program
     */
    class Driver
    {
    public:
        Driver() = default;

        /**
         * @brief Parses the content of a file
         * @param filename A file containing the expressions to evaluate
         */
        void parse(const std::string& filename);

        /**
         * @brief Parses input from a stream
         * @param stream The stream from which the program is getting its input
         */
        void parse(std::istream& stream);

        /**
         * @brief Tells the driver that the parsing should end
         */
        void endParse();

        /**
         * @brief Sets the driver's operating mode
         * @param m The requested mode
         */
        void setMode(Mode m);

        /**
         * @brief Returns the driver's mode
         * @return
         */
        Mode getMode() const;

        /**
         * @brief Returns the driver's current location
         * @return The location of the last token processed by the scanner
         */
        ccalc::location& getLocation();

        /**
         * @brief Sets the last result
         * @param f A Float
         */
        void setLastResult(const Float& f);

        /**
         * @brief Returns the result of the last expression
         * @return The result of the last expression if it wasn't a variable assignement
         */
        Float getLastResult() const;

        /**
         * @brief Adds a variable
         * @param name The variable's name
         * @param value The variable's value
         */
        void addVariable(const std::string& name, Float value);

        /**
         * @brief Retrieves a variable's value
         * @param name The variable's name
         * @throw ccalc::UndefinedIdentifier The variable was not previously defined
         * @return The variable's value
         */
        Float getVariable(const std::string& name) const;

        /**
         * @brief Calls a function
         *
         * Mathematical functions return a ccalc::Float and take as a single argument a
         * std::vector<ccalc::Float> which contains the arguments for the actual function
         * call
         *
         * @param name The function's name
         * @param args The arguments to provide to the function
         * @throw ccalc::UndefinedIdentifier The requested function does not exist
         * @trhow ccalc::InvalidArgument The number of arguments is wrong or the arguments
         *        themselves are invalid
         * @return The result of the function call
         */
        Float call(const std::string& name, const std::vector<Float>& args) const;

        /**
         * @brief Calls a system (i.e. not a mathematical) function
         * @param name The function's name
         * @param args The arguments to provide to the function
         * @throw ccalc::UndefinedIdentifier The requested function does not exist
         * @trhow ccalc::InvalidArgument The number of arguments is wrong or the arguments
         *        themselves are invalid
         */
        void callSysFunction(const std::string& name, const std::vector<Float>& args) const;

    private:
        ccalc::location loc;
        ccalc::Mode driverMode = Mode::interactive;
        Float lastResult;
        std::unordered_map<std::string, Float> variables;
        bool shouldEnd = false;

        const static std::unordered_map<std::string, Float> predefinedVariables;
        const static std::unordered_map<std::string, std::function<Float(const std::vector<Float>&)>> functions;
        const static std::unordered_map<std::string, std::function<void(const std::vector<Float>&)>> sysFunctions;
    };

    /**
     * @brief Namespace containing the mathematical functions
     */
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

    /**
     * @brief Namespace containing non-mathematical functions
     */
    namespace sys
    {
        /**
         * @brief Sets the number of significant digits to use in the output
         */
        void setPrecision(const std::vector<Float>& args);
    } // namespace sys
} // namespace ccalc

#endif // !DRIVER_HPP
