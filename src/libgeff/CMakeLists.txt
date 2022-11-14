file(GLOB_RECURSE HSRC ${PROJECT_SOURCE_DIR}/src/public/libgeff/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${PROJECT_SOURCE_DIR}/src/public)

if(MSVC)
    set(CMAKE_C_FLAGS "/O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(libgeff ${DVM_BUILD_TYPE} ${HSRC} ${SRC})

target_include_directories(libgeff PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libgeff>
        $<INSTALL_INTERFACE:include>
        )
