CPMAddPackage(
  NAME Catch2
  GITHUB_REPOSITORY catchorg/Catch2
  VERSION 2.13.7
  OPTIONS "BUILD_TESTING OFF" "CATCH_DEVELOPMENT_BUILD OFF" "CATCH_INSTALL_DOCS OFF" "CATCH_INSTALL_HELPERS OFF" "BUILD_TESTING OFF"
)

set(TEST_SOURCES main.cpp test_helper.cpp basic_operations.cpp basic_functions.cpp trigonometric_functions.cpp)

foreach(FILE ${FLEX_OUTPUT})
  set_source_files_properties(${FILE} PROPERTIES GENERATED TRUE)
endforeach()
foreach(FILE ${BISON_OUTPUT})
  set_source_files_properties(${FILE} PROPERTIES GENERATED TRUE)
endforeach()

add_executable(ccalc_test)
add_dependencies(ccalc_test generated_sources)
target_sources(ccalc_test PRIVATE ${TEST_SOURCES} ${COMMON_SOURCES})
target_link_libraries(
  ccalc_test
  PRIVATE Catch2::Catch2
  PRIVATE Boost::boost
)
target_include_directories(ccalc_test PRIVATE ${COMMON_INCLUDE})

if(CCALC_ENABLE_CTEST)
  list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/contrib/")
  include(CTest)
  enable_testing()
  include(Catch)
  catch_discover_tests(ccalc_test)
endif()

install(TARGETS ccalc_test RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/test)
