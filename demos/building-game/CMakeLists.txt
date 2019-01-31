project(building_game_demo CXX)

file(GLOB_RECURSE source_files *.cpp *.h *.c *.hpp)
add_executable(building_game_demo ${source_files})

target_link_libraries(building_game_demo hourglass GL dl glfw)
target_include_directories(building_game_demo PRIVATE .)
