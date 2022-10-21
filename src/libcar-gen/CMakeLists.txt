file(GLOB_RECURSE PHSRC ${CMAKE_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

#file(GLOB_RECURSE TEST ${PROJECT_SOURCE_DIR}/?opcode*.h)

include_directories(${PROJECT_SOURCE_DIR}/src/public)
include_directories(${PROJECT_SOURCE_DIR}/src/public/libdvm)

add_library(libcar-gen STATIC ${SRC} ${PHSRC} ${HSRC})
set_target_properties(libcar PROPERTIES OUTPUT_NAME "car-gen")
