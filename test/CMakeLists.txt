file(GLOB_RECURSE testSources "*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(lgTest ${testSources})
target_link_libraries(lgTest lgLib)
