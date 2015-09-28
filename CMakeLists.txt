cmake_minimum_required(VERSION 2.8)
project(LinkedGrid)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

if(WIN32)
    set(ExternalLibraryLocation "${PROJECT_SOURCE_DIR}/../../ext")
    set(CMAKE_PREFIX_PATH "${ExternalLibraryLocation}/SFML-2.2-compiled")
endif()

# External libraries
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)
#find_package(SFML 2 REQUIRED system window graphics network audio)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(test_gui)
