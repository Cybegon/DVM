file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/libdvm/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
#file(GLOB_RECURSE INC ${CMAKE_CURRENT_SOURCE_DIR}/*.inc)

if(MSVC)
    set(CMAKE_C_FLAGS "/O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(libdvm ${DVM_BUILD_TYPE} ${SRC} ${HSRC} ${PHSRC})
target_link_libraries(libdvm PRIVATE datatypes)

target_include_directories(libdvm PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libdvm>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>>
        )

install(TARGETS libdvm
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )

install(FILES ${PHSRC} DESTINATION include/libdvm)