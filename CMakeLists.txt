cmake_minimum_required(VERSION 3.11)
project(hourglass_sdk)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(version)

option(BUILD_DEMOS "Build Demos" OFF)
option(BUILD_TESTS "Build tests for SDK" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

message(STATUS "BUILD_DEMOS: " ${BUILD_DEMOS})
message(STATUS "BUILD_TESTS: " ${BUILD_TESTS})

add_subdirectory(third_party)

add_subdirectory(lib)

if(BUILD_DEMOS)
    add_subdirectory(demos)
endif()

if(BUILD_TESTS)
    enable_testing()
    include(conan)
    conan_check(VERSION 1.10.0 REQUIRED)

    conan_add_remote(NAME bincrafters URL https://api.bintray.com/conan/bincrafters/public-conan)

    conan_cmake_run(
            REQUIRES
                    gtest/1.8.1@bincrafters/stable

            BASIC_SETUP
            CMAKE_TARGETS
            BUILD missing)

    add_subdirectory(tests)
endif()
