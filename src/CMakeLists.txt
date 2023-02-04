add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libgeff)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dvm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libdvm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libcar)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libcar-gen)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libdvm-base)

file(GLOB HRC ${CMAKE_CURRENT_SOURCE_DIR}/public/*.h)
install(FILES )