cmake_minimum_required(VERSION 3.12)

add_executable("ExampleHashMap" "ExampleHashMap.cpp")
target_include_directories("ExampleHashMap" PRIVATE "${CMAKE_SOURCE_DIR}/include/mini-stl")
target_link_libraries("ExampleHashMap" INTERFACE "mini-stl")
set_cpp_20("ExampleHashMap")
set_debug_mode("ExampleHashMap")