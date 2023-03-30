add_executable(dvm main.c)
target_link_libraries(dvm datatypes libdvm-base libcar)

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl /O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-O3")
endif()

install(TARGETS dvm
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )

install(FILES ${PROJECT_SOURCE_DIR}/test/VM.dex DESTINATION bin)

file(COPY ${PROJECT_SOURCE_DIR}/test/VM.dex
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

