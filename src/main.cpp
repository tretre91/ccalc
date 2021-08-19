#include "driver.hpp"
#include <argh.h>
#include <iostream>

#ifdef _WIN32
#    include <io.h>
#    define isatty _isatty
#    define fileno _fileno
#else
#    include <unistd.h>
#endif

constexpr const char* help_message =
  "Usage:\n"
  "    ccalc\n"
  "    ccalc -e EXPRESSION\n"
  "    ccalc -f FILE\n\n"
  "Options:\n"
  "  -h, --help        display this help message\n"
  "  -e, --eval EXPR   evaluate the content of EXPR\n"
  "  -f, --file FILE   process the content of FILE\n\n"
  "See the full documentation at https://github.com/tretre91/ccalc/blob/master/README.md\n";

int main(int argc, char* argv[]) {
    argh::parser argParse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);
    ccalc::Driver driver;

    if (argParse[{"-h", "--help"}]) {
        std::cout << '\n' << help_message << '\n';
    } else if (!isatty(fileno(stdin))) {
        driver.setMode(ccalc::Mode::file);
        driver.parse(std::cin);
    } else if (argParse({"-e", "--eval"})) {
        driver.setMode(ccalc::Mode::eval);
        driver.parse(argParse({"-e", "--eval"}));
    } else if (argParse({"-f", "--file"})) {
        driver.setMode(ccalc::Mode::file);
        driver.parse(argParse({"-f", "--file"}).str());
    } else {
        driver.setMode(ccalc::Mode::interactive);
        driver.parse(std::cin);
    }
    return 0;
}
