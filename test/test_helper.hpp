#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP

#include <boost/math/constants/constants.hpp>
#include <catch2/catch.hpp>
#include <driver.hpp>

class Helper
{
public:
    const static ccalc::Float epsilon;
    const static ccalc::Float root_3;
    const static ccalc::Float root_3_2;
    const static ccalc::Float root_2_2;
    const static ccalc::Float inf;

    const static Approx zero;
    const static Approx one;
    const static Approx half;
    const static Approx half_root_three;
    const static Approx half_root_two;
    const static Approx root_three;
    const static Approx one_over_root_three;

    /**
     * @brief Constructs the string corresponding to a function call
     * @tparam ...Args The arguments' type **must** be ccalc::Float
     * @param name The function's name
     * @param ...args The arguments
     * @return A string of the form *name(arg1, arg2, ... argn)*
     */
    template<typename... Args>
    static std::string makeFunctionCall(const std::string& name, const Args&... args) {
        return name + '(' + unpack(args...) + ')';
    }

private:
    static std::string unpack(const ccalc::Float& arg) {
        return arg.str();
    }

    template<typename... Args>
    static std::string unpack(const ccalc::Float& arg, const Args&... args) {
        return arg.str() + ", " + unpack(args...);
    }
};

/**
 * @brief Evaluates an expression
 * @param driver
 * @param expr The expression to evaluate (a single expression or multiple expressions
 *             separated by a newline character)
 * @return The result of the expression
 */
ccalc::Float eval(ccalc::Driver& driver, const std::string& expr);

#endif // !TEST_HELPER_HPP
