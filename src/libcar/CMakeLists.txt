file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/i32)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/i64)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/src/public)
#include_directories(${PROJECT_SOURCE_DIR}/src/public/libdvm)

add_library(libcar STATIC ${SRC} ${PHSRC} ${HSRC})
target_link_libraries(libcar INTERFACE libdvm)
set_target_properties(libcar PROPERTIES OUTPUT_NAME "car")

target_include_directories(libcar PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libcar>
        $<INSTALL_INTERFACE:include/libcar>
        )
