file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_SOURCE_DIR}/src/public)

add_executable(dvm-runtime ${SRC} ${HSRC})
