#include "test_helper.hpp"
#include <catch2/catch.hpp>

TEST_CASE("abs function", "[mathematical functions][basic functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("negative values") {
        auto numbers = GENERATE(range(-1e10, -0.0, 1.27648378e7));
        const auto val = ccalc::Float(numbers);
        REQUIRE(eval(driver, Helper::makeFunctionCall("abs", val)) == -val);
    }

    SECTION("zero") {
        const ccalc::Float zero(0.0);
        REQUIRE(eval(driver, "abs(-0)") == zero);
        REQUIRE(eval(driver, "abs(0)") == zero);
        REQUIRE(eval(driver, "abs(-0.0)") == zero);
        REQUIRE(eval(driver, "abs(0.0)") == zero);
    }

    SECTION("positive values") {
        auto numbers = GENERATE(range(0.0, 1e10, 1.27648378e7));
        const auto val = ccalc::Float(numbers);
        REQUIRE(eval(driver, Helper::makeFunctionCall("abs", val)) == val);
    }
}

TEST_CASE("sqrt function", "[mathematical functions][basic functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("zero and one") {
        const ccalc::Float zero(0.0);
        REQUIRE(eval(driver, "sqrt(0)") == zero);
        REQUIRE(eval(driver, "sqrt(-0)") == zero);
        REQUIRE(eval(driver, "sqrt(0.)") == zero);
        REQUIRE(eval(driver, "sqrt(-.0)") == zero);

        const ccalc::Float one(1.0);
        REQUIRE(eval(driver, "sqrt(1)") == one);
        REQUIRE(boost::multiprecision::isnan(eval(driver, "sqrt(-1)")));
        REQUIRE(eval(driver, "sqrt(1.)") == one);
        REQUIRE(boost::multiprecision::isnan(eval(driver, "sqrt(-1.0)")));
    }

    SECTION("random values") {
        auto numbers = GENERATE(take(100, random(0.0, std::numeric_limits<double>::max())));
        const auto val = ccalc::Float(numbers);
        const auto res = eval(driver, Helper::makeFunctionCall("sqrt", val));
        REQUIRE(res * res == Approx(val).margin(Helper::epsilon));
    }
}

TEST_CASE("min function", "[mathematical functions][basic functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    auto a_ = GENERATE(take(5, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    auto b_ = GENERATE(take(5, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, Helper::makeFunctionCall("min", a, b)) == std::min({a, b}));

    auto c_ = GENERATE(take(5, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float c(c_);
    REQUIRE(eval(driver, Helper::makeFunctionCall("min", a, b, c)) == std::min({a, b, c}));
}

TEST_CASE("max function", "[mathematical functions][basic functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    auto a_ = GENERATE(take(5, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float a(a_);
    auto b_ = GENERATE(take(5, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float b(b_);
    REQUIRE(eval(driver, Helper::makeFunctionCall("max", a, b)) == std::max({a, b}));

    auto c_ = GENERATE(take(5, random(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())));
    const ccalc::Float c(c_);
    REQUIRE(eval(driver, Helper::makeFunctionCall("max", a, b, c)) == std::max({a, b, c}));
}
