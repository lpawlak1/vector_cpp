cmake_minimum_required(VERSION 3.16)
project(data_structure)

set(CMAKE_CXX_STANDARD 11) 
include_directories(src)
file(GLOB SOURCES "src/*.hpp" "src/*.h")


add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(tests)
