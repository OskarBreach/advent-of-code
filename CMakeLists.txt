cmake_minimum_required(VERSION 3.15.0)

project(AdventOfCode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(gppUnit)
add_subdirectory(parsing)
add_subdirectory(advent2020)

add_subdirectory(src)
add_subdirectory(test)
