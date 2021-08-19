#include "test_helper.hpp"
#include <sstream>

namespace mc = boost::math::constants;

const ccalc::Float Helper::epsilon = std::numeric_limits<ccalc::Float>::epsilon();
const ccalc::Float Helper::root_3 = mc::root_three<ccalc::Float>();
const ccalc::Float Helper::root_3_2 = root_3 * mc::half<ccalc::Float>();
const ccalc::Float Helper::root_2_2 = mc::root_two<ccalc::Float>() * mc::half<ccalc::Float>();
const ccalc::Float Helper::inf = std::numeric_limits<ccalc::Float>::infinity();

const Approx Helper::zero = Approx(ccalc::Float(0.0)).margin(epsilon);
const Approx Helper::one = Approx(ccalc::Float(1.0)).margin(epsilon);
const Approx Helper::half = Approx(mc::half<ccalc::Float>()).margin(epsilon);
const Approx Helper::half_root_three = Approx(root_3_2).margin(epsilon);
const Approx Helper::half_root_two = Approx(root_2_2).margin(epsilon);
const Approx Helper::root_three = Approx(root_3).margin(epsilon);
const Approx Helper::one_over_root_three = Approx(ccalc::Float(1.0) / root_3).margin(epsilon);

ccalc::Float eval(ccalc::Driver& driver, const std::string& expr) {
    std::istringstream is(expr);
    driver.parse(is);
    return driver.getLastResult();
}