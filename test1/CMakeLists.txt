cmake_minimum_required (VERSION 3.15)

project (test1)

include_directories ("${PROJECT_SOURCE_DIR}/include")

aux_source_directory (. sourceList)

add_subdirectory (lib)

add_executable(test1 ${sourceList})

target_link_libraries (test1 lib)