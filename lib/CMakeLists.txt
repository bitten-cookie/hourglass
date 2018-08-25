project(hourglass CXX)

configure_file(config.hpp.in ${CMAKE_BINARY_DIR}/include/hourglass/config.hpp)

file(GLOB_RECURSE source_files *.cpp *.hpp)
add_library(hourglass STATIC ${source_files})

target_include_directories(hourglass
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    cpp
    src
)

set_target_properties(hourglass PROPERTIES LINKER_LANGUAGE CXX)

target_compile_options(hourglass PRIVATE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wduplicated-cond
        -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wold-style-cast -Wno-useless-cast
        -Wdouble-promotion -Wno-unknown-pragmas
        -Wformat=2 -pedantic
)

# Todo: add install targets