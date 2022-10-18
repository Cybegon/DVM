file(GLOB_RECURSE PHSRC ${CMAKE_SOURCE_DIR}/src/public/libgeff/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_SOURCE_DIR}/src/public)

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(geff STATIC ${PHSRC} ${SRC})