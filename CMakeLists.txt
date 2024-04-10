cmake_minimum_required(VERSION 3.15)

project (main)

add_compile_options(-std=c11 -w)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory (src SRC_LIST)

include_directories (inc)

add_executable (main ${SRC_LIST})