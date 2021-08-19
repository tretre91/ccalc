cmake_minimum_required(VERSION 3.14)

project(
  ccalc
  LANGUAGES CXX
  VERSION 0.0.1
  DESCRIPTION "A command line calculator"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

option(CCALC_TESTS "Builds a test executable" OFF)
option(CCALC_ENABLE_CTEST "Registers the tests in CTest and enable testing targets" OFF)

find_package(Boost 1.67.0 REQUIRED)

include(CPM)
include(GNUInstallDirs)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CCALC_FLEX
    flex
    CACHE STRING "Name of the flex executable"
)
set(FLEX_SOURCE ${SOURCE_DIR}/calc.l)
set(FLEX_OUTPUT ${OUTPUT_DIR}/scanner.cc)
set(FLEX_FLAGS "--outfile=scanner.cc")
set(CCALC_FLEX_FLAGS
    ""
    CACHE STRING "Additional flags to pass to flex"
)

set(CCALC_BISON
    bison
    CACHE STRING "Name of the bison executable"
)
set(BISON_SOURCE ${SOURCE_DIR}/calc.yy)
set(BISON_OUTPUT ${OUTPUT_DIR}/parser.hh ${OUTPUT_DIR}/parser.cc ${OUTPUT_DIR}/location.hh)
set(CCALC_BISON_FLAGS
    ""
    CACHE STRING "Additional flags to pass to bison"
)

# Call flex
add_custom_command(
  OUTPUT ${FLEX_OUTPUT}
  COMMAND ${CCALC_FLEX} ${FLEX_FLAGS} ${CCALC_FLEX_FLAGS} ${FLEX_SOURCE}
  MAIN_DEPENDENCY ${FLEX_SOURCE}
)

# Call bison
add_custom_command(
  OUTPUT ${BISON_OUTPUT}
  COMMAND ${CCALC_BISON} ${CCALC_BISON_FLAGS} ${BISON_SOURCE}
  MAIN_DEPENDENCY ${BISON_SOURCE}
)

# Add a custom target that depends on the generated files to allow incremental builds
add_custom_target(generated_sources ALL DEPENDS ${FLEX_OUTPUT} ${BISON_OUTPUT})

set(COMMON_SOURCES ${SOURCE_DIR}/driver.cpp ${OUTPUT_DIR}/scanner.cc ${OUTPUT_DIR}/parser.cc)
set(COMMON_INCLUDE ${SOURCE_DIR} ${OUTPUT_DIR})

add_subdirectory(src)
if(CCALC_TESTS)
  add_subdirectory(test)
endif()

install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
