CPMAddPackage(
  NAME argh
  GITHUB_REPOSITORY adishavit/argh
  GIT_TAG v1.3.1
  OPTIONS "BUILD_TESTS OFF" "BUILD_EXAMPLES OFF"
  EXCLUDE_FROM_ALL TRUE
)

foreach(FILE ${FLEX_OUTPUT})
  set_source_files_properties(${FILE} PROPERTIES GENERATED TRUE)
endforeach()
foreach(FILE ${BISON_OUTPUT})
  set_source_files_properties(${FILE} PROPERTIES GENERATED TRUE)
endforeach()

add_executable(ccalc)
add_dependencies(ccalc generated_sources)
target_sources(ccalc PRIVATE main.cpp ${COMMON_SOURCES})

target_link_libraries(
  ccalc
  PRIVATE argh
  PRIVATE Boost::boost
)
target_include_directories(ccalc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${COMMON_INCLUDE})

install(TARGETS ccalc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
