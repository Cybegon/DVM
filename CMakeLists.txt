cmake_minimum_required(VERSION 3.15)

project(VirtualDragon VERSION 0.0.56 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/zip)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
