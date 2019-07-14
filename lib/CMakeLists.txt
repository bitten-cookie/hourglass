project(hourglass CXX)

configure_file(config.hpp.in ${CMAKE_BINARY_DIR}/include/hourglass/config.hpp)

add_library(hourglass INTERFACE)

target_include_directories(hourglass
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(hourglass INTERFACE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wduplicated-cond
        -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wold-style-cast -Wno-useless-cast
        -Wdouble-promotion -Wno-unknown-pragmas
        -Wformat=2 -pedantic
)

# Todo: add install targets