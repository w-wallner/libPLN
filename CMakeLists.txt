cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("libPLN")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

add_subdirectory(src)
add_subdirectory(Tests)
add_subdirectory(Examples)
