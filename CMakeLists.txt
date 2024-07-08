cmake_minimum_required(VERSION 3.15)

project(VirtualDragon VERSION 0.6.121 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)

option(BUILD_SHARED_LIBS "Build the shared libraries" OFF)

set(DVM_BUILD_TYPE STATIC)
if(BUILD_SHARED_LIBS)
    set(DVM_BUILD_TYPE SHARED)
endif()

if (NOT TARGET datatypes)
    add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/datatypes.h)
endif()

set(ZLIB_TAG "develop")
set(MZ_COMPAT OFF)
set(MZ_BZIP2 OFF)
set(MZ_LZMA OFF)
set(MZ_ZSTD OFF)
set(MZ_LIBCOMP OFF)
set(MZ_FETCH_LIBS ON)
set(MZ_PKCRYPT OFF)
set(MZ_WZAES OFF)
set(MZ_OPENSSL OFF)
set(MZ_LIBBSD OFF)
set(MZ_ICONV OFF)
set(MZ_DECOMPRESS_ONLY ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/extlibs/minizip-ng)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_IMPORT_LIBRARY_PREFIX "")

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
