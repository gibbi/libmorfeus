cmake_minimum_required(VERSION 3.6)

project(libmorfeus
    VERSION 0.0
    LANGUAGES CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


FIND_PACKAGE(HIDAPI)

add_subdirectory(src)


