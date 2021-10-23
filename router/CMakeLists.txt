cmake_minimum_required(VERSION 3.5)
project(629_router)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)

include_directories(.)
add_subdirectory(easygl)
add_subdirectory(src)
