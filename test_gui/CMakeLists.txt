file(GLOB_RECURSE testGuiSources "*.cpp")

include_directories(${SFML_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(lgTestGui ${testGuiSources})
target_link_libraries(lgTestGui lgLib)
target_link_libraries(lgTestGui ${SFML_LIBRARIES})
