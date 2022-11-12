file(GLOB PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
#file(GLOB_RECURSE INC ${CMAKE_CURRENT_SOURCE_DIR}/*.inc)

include_directories(${PROJECT_SOURCE_DIR}/src/public)
include_directories(${PROJECT_SOURCE_DIR}/src/public/libdvm)

#message(${PHSRC})

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(libdvm ${DVM_BUILD_TYPE} ${SRC} ${PHSRC} ${HSRC})

target_include_directories(libdvm PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libdvm>
        $<INSTALL_INTERFACE:include>
        )
