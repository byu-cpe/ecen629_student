cmake_minimum_required(VERSION 3.5)
project(629_placer)

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_subdirectory(easygl)
add_subdirectory(src)
