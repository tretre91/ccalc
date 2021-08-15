#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP

#include "../common.hpp"
#include "../include/catch.hpp"
#include <boost/math/constants/constants.hpp>
#include <sstream>

namespace test
{
    namespace mc = boost::math::constants;

    const static ccalc::Float epsilon = std::numeric_limits<ccalc::Float>::epsilon();
    const static ccalc::Float root_3 = mc::root_three<ccalc::Float>();
    const static ccalc::Float root_3_2 = root_3 * mc::half<ccalc::Float>();
    const static ccalc::Float root_2_2 = mc::root_two<ccalc::Float>() * mc::half<ccalc::Float>();
    const static ccalc::Float inf = std::numeric_limits<ccalc::Float>::infinity();

    const static Approx zero = Approx(ccalc::Float(0.0)).margin(epsilon);
    const static Approx one = Approx(ccalc::Float(1.0)).margin(epsilon);
    const static Approx half = Approx(mc::half<ccalc::Float>()).margin(epsilon);
    const static Approx half_root_three = Approx(root_3_2).margin(epsilon);
    const static Approx half_root_two = Approx(root_2_2).margin(epsilon);
    const static Approx root_three = Approx(root_3).margin(epsilon);
    const static Approx one_over_root_three = Approx(ccalc::Float(1.0) / root_3).margin(epsilon);

    ccalc::Float eval(ccalc::Driver& driver, const std::string& expr) {
        driver.parse(std::istringstream(expr));
        return driver.getLastResult();
    }
} // namespace test

#endif // !TEST_HELPER_HPP