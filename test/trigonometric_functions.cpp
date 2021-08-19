#include "test_helper.hpp"
#include <catch2/catch.hpp>

// Angles are tested in the following order: 0, pi/6, pi/4, pi/3, pi/2, 2*pi/3, 3*pi/4, 5*pi/6, pi, 3*pi/2, 2*pi

TEST_CASE("cos function", "[mathematical functions][trigonometric functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("positive angles") {
        REQUIRE(eval(driver, "cos(0)") == Helper::one);
        REQUIRE(eval(driver, "cos(pi/6)") == Helper::half_root_three);
        REQUIRE(eval(driver, "cos(pi/4)") == Helper::half_root_two);
        REQUIRE(eval(driver, "cos(pi/3)") == Helper::half);
        REQUIRE(eval(driver, "cos(pi/2)") == Helper::zero);
        REQUIRE(eval(driver, "cos(2*pi/3)") == -Helper::half);
        REQUIRE(eval(driver, "cos(3*pi/4)") == -Helper::half_root_two);
        REQUIRE(eval(driver, "cos(5*pi/6)") == -Helper::half_root_three);
        REQUIRE(eval(driver, "cos(pi)") == -Helper::one);
        REQUIRE(eval(driver, "cos(3*pi/2)") == Helper::zero);
        REQUIRE(eval(driver, "cos(2*pi)") == Helper::one);
    }

    SECTION("negative angles") {
        REQUIRE(eval(driver, "cos(-0)") == Helper::one);
        REQUIRE(eval(driver, "cos(-pi/6)") == Helper::half_root_three);
        REQUIRE(eval(driver, "cos(-pi/4)") == Helper::half_root_two);
        REQUIRE(eval(driver, "cos(-pi/3)") == Helper::half);
        REQUIRE(eval(driver, "cos(-pi/2)") == Helper::zero);
        REQUIRE(eval(driver, "cos(-2*pi/3)") == -Helper::half);
        REQUIRE(eval(driver, "cos(-3*pi/4)") == -Helper::half_root_two);
        REQUIRE(eval(driver, "cos(-5*pi/6)") == -Helper::half_root_three);
        REQUIRE(eval(driver, "cos(-pi)") == -Helper::one);
        REQUIRE(eval(driver, "cos(-3*pi/2)") == Helper::zero);
        REQUIRE(eval(driver, "cos(-2*pi)") == Helper::one);
    }
}

TEST_CASE("sin function", "[mathematical functions][trigonometric functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("positive angles") {
        REQUIRE(eval(driver, "sin(0)") == Helper::zero);
        REQUIRE(eval(driver, "sin(pi/6)") == Helper::half);
        REQUIRE(eval(driver, "sin(pi/4)") == Helper::half_root_two);
        REQUIRE(eval(driver, "sin(pi/3)") == Helper::half_root_three);
        REQUIRE(eval(driver, "sin(pi/2)") == Helper::one);
        REQUIRE(eval(driver, "sin(2*pi/3)") == Helper::half_root_three);
        REQUIRE(eval(driver, "sin(3*pi/4)") == Helper::half_root_two);
        REQUIRE(eval(driver, "sin(5*pi/6)") == Helper::half);
        REQUIRE(eval(driver, "sin(pi)") == Helper::zero);
        REQUIRE(eval(driver, "sin(3*pi/2)") == -Helper::one);
        REQUIRE(eval(driver, "sin(2*pi)") == Helper::zero);
    }

    SECTION("negative angles") {
        REQUIRE(eval(driver, "sin(-0)") == Helper::zero);
        REQUIRE(eval(driver, "sin(-pi/6)") == -Helper::half);
        REQUIRE(eval(driver, "sin(-pi/4)") == -Helper::half_root_two);
        REQUIRE(eval(driver, "sin(-pi/3)") == -Helper::half_root_three);
        REQUIRE(eval(driver, "sin(-pi/2)") == -Helper::one);
        REQUIRE(eval(driver, "sin(-2*pi/3)") == -Helper::half_root_three);
        REQUIRE(eval(driver, "sin(-3*pi/4)") == -Helper::half_root_two);
        REQUIRE(eval(driver, "sin(-5*pi/6)") == -Helper::half);
        REQUIRE(eval(driver, "sin(-pi)") == Helper::zero);
        REQUIRE(eval(driver, "sin(-3*pi/2)") == Helper::one);
        REQUIRE(eval(driver, "sin(-2*pi)") == Helper::zero);
    }
}

TEST_CASE("tan function", "[mathematical functions][trigonometric functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("positive angles") {
        REQUIRE(eval(driver, "tan(0)") == Helper::zero);
        REQUIRE(eval(driver, "tan(pi/6)") == Helper::one_over_root_three);
        REQUIRE(eval(driver, "tan(pi/4)") == Helper::one);
        REQUIRE(eval(driver, "tan(pi/3)") == Helper::root_three);
        REQUIRE(eval(driver, "tan(pi/2)") == Helper::inf);
        REQUIRE(eval(driver, "tan(2*pi/3)") == -Helper::root_three);
        REQUIRE(eval(driver, "tan(3*pi/4)") == -Helper::one);
        REQUIRE(eval(driver, "tan(5*pi/6)") == -Helper::one_over_root_three);
        REQUIRE(eval(driver, "tan(pi)") == Helper::zero);
        REQUIRE(eval(driver, "tan(3*pi/2)") == -Helper::inf);
        REQUIRE(eval(driver, "tan(2*pi)") == Helper::zero);
    }

    SECTION("negative angles") {
        REQUIRE(eval(driver, "tan(-0)") == Helper::zero);
        REQUIRE(eval(driver, "tan(-pi/6)") == -Helper::one_over_root_three);
        REQUIRE(eval(driver, "tan(-pi/4)") == -Helper::one);
        REQUIRE(eval(driver, "tan(-pi/3)") == -Helper::root_three);
        REQUIRE(eval(driver, "tan(-pi/2)") == -Helper::inf);
        REQUIRE(eval(driver, "tan(-2*pi/3)") == Helper::root_three);
        REQUIRE(eval(driver, "tan(-3*pi/4)") == Helper::one);
        REQUIRE(eval(driver, "tan(-5*pi/6)") == Helper::one_over_root_three);
        REQUIRE(eval(driver, "tan(-pi)") == Helper::zero);
        REQUIRE(eval(driver, "tan(-3*pi/2)") == Helper::inf);
        REQUIRE(eval(driver, "tan(-2*pi)") == Helper::zero);
    }
}