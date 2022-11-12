file(GLOB PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
#file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${PROJECT_SOURCE_DIR}/src/libdvm-base)
include_directories(${PROJECT_SOURCE_DIR}/src/public)

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl /O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-O3")
endif()

add_library(libdvm-base ${DVM_BUILD_TYPE} dvmbase.c ${PHSRC})
target_link_libraries(libdvm-base INTERFACE libdvm PRIVATE libgeff zip)

target_include_directories(libdvm-base PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libdvm-base>
        $<INSTALL_INTERFACE:include>
        )
