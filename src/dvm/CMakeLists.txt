add_executable(DVM main.c)
include_directories(${CMAKE_SOURCE_DIR}/src/public)
target_link_libraries(DVM dvm dvm-base)

file(COPY ${CMAKE_SOURCE_DIR}/test/VM.dex
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})