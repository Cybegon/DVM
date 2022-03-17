add_executable(DVM main.c memory.c memory.h)
include_directories(${CMAKE_SOURCE_DIR}/src/public)
target_link_libraries(DVM dvm)
