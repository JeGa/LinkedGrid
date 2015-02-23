set(main "main.cpp")
file(GLOB_RECURSE sources "*.cpp")
list(REMOVE_ITEM sources ${main})

add_library(lgLib ${sources})
add_executable(lg ${main})
link_libraries(lg lgLib)