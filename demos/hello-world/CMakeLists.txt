project(hello_world_demo CXX)

file(GLOB_RECURSE source_files *.cpp *.h)
add_executable(hello_world_demo ${source_files})

target_link_libraries(hello_world_demo hourglass)
target_include_directories(hello_world_demo PRIVATE .)
