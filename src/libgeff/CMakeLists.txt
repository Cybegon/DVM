file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/libgeff/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${PROJECT_SOURCE_DIR}/src/public)

if(MSVC)
    set(CMAKE_C_FLAGS "/O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(libgeff ${DVM_BUILD_TYPE} ${PHSRC} ${SRC})
target_link_libraries(libgeff PRIVATE datatypes)

target_include_directories(libgeff PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libgeff>
        $<INSTALL_INTERFACE:include>
        )

install(TARGETS libgeff
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )

install(FILES ${PHSRC} DESTINATION include/libgeff)
