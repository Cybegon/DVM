file(GLOB_RECURSE PHSRC ${CMAKE_SOURCE_DIR}/src/public/*.h)
#file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_SOURCE_DIR}/src/libdvm-base)

include_directories(${CMAKE_SOURCE_DIR}/src/public)
include_directories(${CMAKE_SOURCE_DIR}/src/public/libdvm)
include_directories(${CMAKE_SOURCE_DIR}/src/public/libdvm-base)

if(MSVC)
#    set(CMAKE_C_FLAGS "/sdl")
#    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
#    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX)
#    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -Ofast")
    #set(CMAKE_STATIC_LINKER_FLAGS "-nolibc")
endif()

add_library(dvm-base STATIC dvmbase.c ${PHSRC})
target_link_libraries(dvm-base geff zip)