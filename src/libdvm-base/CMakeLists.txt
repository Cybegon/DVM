file(GLOB PHSRC ${PROJECT_SOURCE_DIR}/src/public/libdvm-base/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ext/*/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/common/*/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.c)

if(MSVC)
    set(CMAKE_C_FLAGS "/sdl /O2")
    set(CMAKE_SHARED_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO /sdl")
    set(CMAKE_STATIC_LINKER_FLAGS "/NODEFAULTLIB /NOLOGO")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "-O3")
endif()

add_library(libdvm-base ${DVM_BUILD_TYPE} ${SRC} ${HSRC} ${PHSRC})
target_link_libraries(libdvm-base
        PUBLIC
            datatypes
            libdvm
        PRIVATE
            libgeff
            MINIZIP::minizip
        )

target_include_directories(libdvm-base
        PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libdvm-base>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/ext
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/os>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utils>
        )

install(TARGETS libdvm-base
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )

install(FILES ${PHSRC} DESTINATION include/libdvm-base)
