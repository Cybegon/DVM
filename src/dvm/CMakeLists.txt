add_executable(dvm main.c)
include_directories(${PROJECT_SOURCE_DIR}/src/public)
target_link_libraries(dvm libdvm libdvm-base libcar)

file(COPY ${PROJECT_SOURCE_DIR}/test/VM.dex
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})