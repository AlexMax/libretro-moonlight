# This is not a promise.  This just happens to be the version of CMake I use.
# If you can successfully bump this version down, more power to you.  Also,
# maybe file an issue stating the version you were able to get it working with?
cmake_minimum_required(VERSION 3.11.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(libretro-moonlight C)

add_definitions(-Wall -Wextra)

add_subdirectory(lib)
add_subdirectory(src)
