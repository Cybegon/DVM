file(GLOB PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl /O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-nostartfiles -nodefaultlibs -nostdlib -O3")
endif()

add_library(libcar ${DVM_BUILD_TYPE} ${SRC} ${PHSRC} ${HSRC})
target_link_libraries(libcar PRIVATE datatypes libdvm)

target_include_directories(libcar PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libcar>
        $<INSTALL_INTERFACE:include>
        )

install(TARGETS libcar
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )

install(FILES ${PHSRC} DESTINATION include/libcar)
