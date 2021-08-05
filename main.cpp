#include "argh.h"
#include "driver.hpp"
#include <fstream>
#include <iostream>

#ifdef _WIN32
#    include <io.h>
#else
#    include <unistd.h>
#endif

int main(int argc, char* argv[]) {
    argh::parser argParse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);
    ccalc::Driver driver;

    if (!isatty(fileno(stdin))) { // we're getting input from a pipe
        driver.setMode(ccalc::Mode::file);
        driver.parse(std::cin);
    } else if (argParse({"-e", "--eval"})) {
        driver.setMode(ccalc::Mode::eval);
        driver.parse(argParse({"-e", "--eval"}));
    } else if (argParse(1)) {
        driver.setMode(ccalc::Mode::file);
        driver.parse(argParse(1).str());
    } else {
        driver.setMode(ccalc::Mode::interactive);
        driver.parse(std::cin);
    }
    return 0;
}
