project(hourglass_tests CXX)

find_package(GTest REQUIRED)

file(GLOB_RECURSE source_files *.cpp)

add_executable(hourglass_tests ${source_files})
target_link_libraries(hourglass_tests hourglass GTest::GTest GTest::Main)
add_test(NAME hourglass_tests COMMAND hourglass_tests)
set_target_properties(hourglass_tests PROPERTIES FOLDER tests)
