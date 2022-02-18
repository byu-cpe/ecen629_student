cmake_minimum_required(VERSION 3.5)
project(629_router)

# find x11
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)

include_directories(.)
add_subdirectory(easygl)
add_subdirectory(src)
