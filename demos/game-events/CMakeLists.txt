project(game_events_demo CXX)

file(GLOB_RECURSE source_files *.cpp *.h)
add_executable(game_events_demo ${source_files})

target_link_libraries(game_events_demo hourglass)
target_include_directories(game_events_demo PRIVATE .)
