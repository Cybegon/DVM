cmake_minimum_required(VERSION 3.15)

project(VirtualDragon VERSION 0.0.56 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

option(BUILD_SHARED_LIBS "Build the shared libraries" OFF)

#set(DVM_GLOBAL_C_FLAGS "-s")

set(DVM_BUILD_TYPE STATIC)
if(BUILD_SHARED_LIBS)
    set(DVM_BUILD_TYPE SHARED)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/zip)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_IMPORT_LIBRARY_PREFIX "")

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
