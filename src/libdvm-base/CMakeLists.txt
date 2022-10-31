file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
#file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${PROJECT_SOURCE_DIR}/src/libdvm-base)

include_directories(${PROJECT_SOURCE_DIR}/src/public)
include_directories(${PROJECT_SOURCE_DIR}/src/public/libdvm)
include_directories(${PROJECT_SOURCE_DIR}/src/public/libdvm-base)

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(libdvm-base STATIC dvmbase.c ${PHSRC})
target_link_libraries(libdvm-base libgeff zip)
set_target_properties(libdvm-base PROPERTIES OUTPUT_NAME "dvm-base")

target_include_directories(libdvm-base PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libdvm-base>
        $<INSTALL_INTERFACE:include/libdvm-base>
        )
