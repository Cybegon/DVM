file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

#file(GLOB_RECURSE TEST ${PROJECT_SOURCE_DIR}/?opcode*.h)

include_directories(${PROJECT_SOURCE_DIR}/src/public)
include_directories(${PROJECT_SOURCE_DIR}/src/public/libcar-gen)
include_directories(${PROJECT_SOURCE_DIR}/src/public/libdvm)

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(libcar-gen STATIC ${SRC} ${PHSRC} ${HSRC})
set_target_properties(libcar-gen PROPERTIES OUTPUT_NAME "car-gen")
