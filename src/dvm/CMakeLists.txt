add_executable(DVM main.c)
include_directories(${CMAKE_SOURCE_DIR}/src/public)
target_link_libraries(DVM dvm)
