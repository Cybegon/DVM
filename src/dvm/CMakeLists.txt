add_executable(dvm main.c)
include_directories(${PROJECT_SOURCE_DIR}/src/public)
target_link_libraries(dvm libdvm libdvm-base libcar)

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl /O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-O3")
endif()

file(COPY ${PROJECT_SOURCE_DIR}/test/VM.dex
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
