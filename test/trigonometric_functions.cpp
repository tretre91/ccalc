#include "../driver.hpp"
#include "../include/catch.hpp"
#include "test_helper.hpp"

using namespace test;

// Angles are tested in the following order: 0, pi/6, pi/4, pi/3, pi/2, 2*pi/3, 3*pi/4, 5*pi/6, pi, 3*pi/2, 2*pi

TEST_CASE("cos function", "[mathematical functions][trigonometric functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("positive angles") {
        REQUIRE(eval(driver, "cos(0)") == one);
        REQUIRE(eval(driver, "cos(pi/6)") == half_root_three);
        REQUIRE(eval(driver, "cos(pi/4)") == half_root_two);
        REQUIRE(eval(driver, "cos(pi/3)") == half);
        REQUIRE(eval(driver, "cos(pi/2)") == zero);
        REQUIRE(eval(driver, "cos(2*pi/3)") == -half);
        REQUIRE(eval(driver, "cos(3*pi/4)") == -half_root_two);
        REQUIRE(eval(driver, "cos(5*pi/6)") == -half_root_three);
        REQUIRE(eval(driver, "cos(pi)") == -one);
        REQUIRE(eval(driver, "cos(3*pi/2)") == zero);
        REQUIRE(eval(driver, "cos(2*pi)") == one);
    }

    SECTION("negative angles") {
        REQUIRE(eval(driver, "cos(-0)") == one);
        REQUIRE(eval(driver, "cos(-pi/6)") == half_root_three);
        REQUIRE(eval(driver, "cos(-pi/4)") == half_root_two);
        REQUIRE(eval(driver, "cos(-pi/3)") == half);
        REQUIRE(eval(driver, "cos(-pi/2)") == zero);
        REQUIRE(eval(driver, "cos(-2*pi/3)") == -half);
        REQUIRE(eval(driver, "cos(-3*pi/4)") == -half_root_two);
        REQUIRE(eval(driver, "cos(-5*pi/6)") == -half_root_three);
        REQUIRE(eval(driver, "cos(-pi)") == -one);
        REQUIRE(eval(driver, "cos(-3*pi/2)") == zero);
        REQUIRE(eval(driver, "cos(-2*pi)") == one);
    }
}

TEST_CASE("sin function", "[mathematical functions][trigonometric functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("positive angles") {
        REQUIRE(eval(driver, "sin(0)") == zero);
        REQUIRE(eval(driver, "sin(pi/6)") == half);
        REQUIRE(eval(driver, "sin(pi/4)") == half_root_two);
        REQUIRE(eval(driver, "sin(pi/3)") == half_root_three);
        REQUIRE(eval(driver, "sin(pi/2)") == one);
        REQUIRE(eval(driver, "sin(2*pi/3)") == half_root_three);
        REQUIRE(eval(driver, "sin(3*pi/4)") == half_root_two);
        REQUIRE(eval(driver, "sin(5*pi/6)") == half);
        REQUIRE(eval(driver, "sin(pi)") == zero);
        REQUIRE(eval(driver, "sin(3*pi/2)") == -one);
        REQUIRE(eval(driver, "sin(2*pi)") == zero);
    }

    SECTION("negative angles") {
        REQUIRE(eval(driver, "sin(-0)") == zero);
        REQUIRE(eval(driver, "sin(-pi/6)") == -half);
        REQUIRE(eval(driver, "sin(-pi/4)") == -half_root_two);
        REQUIRE(eval(driver, "sin(-pi/3)") == -half_root_three);
        REQUIRE(eval(driver, "sin(-pi/2)") == -one);
        REQUIRE(eval(driver, "sin(-2*pi/3)") == -half_root_three);
        REQUIRE(eval(driver, "sin(-3*pi/4)") == -half_root_two);
        REQUIRE(eval(driver, "sin(-5*pi/6)") == -half);
        REQUIRE(eval(driver, "sin(-pi)") == zero);
        REQUIRE(eval(driver, "sin(-3*pi/2)") == one);
        REQUIRE(eval(driver, "sin(-2*pi)") == zero);
    }
}

TEST_CASE("tan function", "[mathematical functions][trigonometric functions]") {
    ccalc::Driver driver;
    driver.setMode(ccalc::Mode::test);

    SECTION("positive angles") {
        REQUIRE(eval(driver, "tan(0)") == zero);
        REQUIRE(eval(driver, "tan(pi/6)") == one_over_root_three);
        REQUIRE(eval(driver, "tan(pi/4)") == one);
        REQUIRE(eval(driver, "tan(pi/3)") == root_three);
        REQUIRE(eval(driver, "tan(pi/2)") == inf);
        REQUIRE(eval(driver, "tan(2*pi/3)") == -root_three);
        REQUIRE(eval(driver, "tan(3*pi/4)") == -one);
        REQUIRE(eval(driver, "tan(5*pi/6)") == -one_over_root_three);
        REQUIRE(eval(driver, "tan(pi)") == zero);
        REQUIRE(eval(driver, "tan(3*pi/2)") == -inf);
        REQUIRE(eval(driver, "tan(2*pi)") == zero);
    }

    SECTION("negative angles") {
        REQUIRE(eval(driver, "tan(-0)") == zero);
        REQUIRE(eval(driver, "tan(-pi/6)") == -one_over_root_three);
        REQUIRE(eval(driver, "tan(-pi/4)") == -one);
        REQUIRE(eval(driver, "tan(-pi/3)") == -root_three);
        REQUIRE(eval(driver, "tan(-pi/2)") == -inf);
        REQUIRE(eval(driver, "tan(-2*pi/3)") == root_three);
        REQUIRE(eval(driver, "tan(-3*pi/4)") == one);
        REQUIRE(eval(driver, "tan(-5*pi/6)") == one_over_root_three);
        REQUIRE(eval(driver, "tan(-pi)") == zero);
        REQUIRE(eval(driver, "tan(-3*pi/2)") == inf);
        REQUIRE(eval(driver, "tan(-2*pi)") == zero);
    }
}