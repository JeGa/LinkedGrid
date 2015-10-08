cmake_minimum_required(VERSION 2.8)
project(LinkedGrid)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

if(WIN32)
    set(ExternalLibraryLocation "${PROJECT_SOURCE_DIR}/../../ext")
    set(SFML_ROOT "${ExternalLibraryLocation}/SFML-2.3.2")
    set(SFGUI_ROOT "${ExternalLibraryLocation}/SFGUI-0.3.0")
endif()

# TODO: Make flag for choosing test or gui test.

# External libraries
find_package(SFML 2.3 COMPONENTS system window graphics audio REQUIRED)
find_package(SFGUI REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(test_gui)
