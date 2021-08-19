#include "test_helper.hpp"
#include <catch2/catch.hpp>

TEST_CASE("addition", "[basic operations]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    auto a_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    auto b_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, a.str() + '+' + b.str()) == a + b);
    REQUIRE(eval(driver, b.str() + '+' + a.str()) == a + b);
}

TEST_CASE("substraction", "[basic operations]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);
    const ccalc::Float zero(0);

    auto a_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    auto b_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, a.str() + '-' + b.str()) == a - b);
    REQUIRE(eval(driver, b.str() + '-' + a.str()) == b - a);
    REQUIRE(eval(driver, a.str() + '-' + a.str()) == zero);
    REQUIRE(eval(driver, b.str() + '-' + b.str()) == zero);
}

TEST_CASE("multiplication", "[basic operations]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);
    const ccalc::Float zero(0);

    auto a_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    auto b_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, a.str() + '*' + b.str()) == a * b);
    REQUIRE(eval(driver, b.str() + '*' + a.str()) == a * b);
    REQUIRE(eval(driver, b.str() + "* 0") == zero);
    REQUIRE(eval(driver, b.str() + "* 1") == b);
}

TEST_CASE("division", "[basic operations]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);
    const ccalc::Float zero(0);

    auto a_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    auto b_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, a.str() + '/' + b.str()) == a / b);
    REQUIRE(eval(driver, b.str() + '/' + a.str()) == b / a);
    REQUIRE(eval(driver, std::string("0 / ") + b.str()) == zero);
    REQUIRE(eval(driver, b.str() + "/ 1") == b);
}

namespace mp = boost::multiprecision;

TEST_CASE("exponentiation", "[basic operations]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);
    const ccalc::Float zero(0);
    const ccalc::Float one(1);

    auto a_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    auto b_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, a.str() + "**" + b.str()) == mp::pow(a, b));
    REQUIRE(eval(driver, a.str() + '^' + b.str()) == mp::pow(a, b));
    REQUIRE(eval(driver, std::string("0 ** ") + b.str()) == zero);
    REQUIRE(eval(driver, b.str() + "** 0") == one);
    REQUIRE(eval(driver, b.str() + "** 1") == b);
    REQUIRE(eval(driver, b.str() + "** 2") == b * b);
}

TEST_CASE("modulo", "[basic operations]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    auto a_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    auto b_ = GENERATE(take(20, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, a.str() + '%' + b.str()) == mp::fmod(a, b));
    REQUIRE(eval(driver, b.str() + '%' + a.str()) == mp::fmod(b, a));
    REQUIRE(mp::isnan(eval(driver, b.str() + "% 0")));
}