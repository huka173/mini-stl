cmake_minimum_required(VERSION 3.12)

add_executable("ExampleList" "ExampleList.cpp")
target_include_directories("ExampleList" PRIVATE "${CMAKE_SOURCE_DIR}/include/mini-stl")
target_link_libraries("ExampleList" INTERFACE "mini-stl")
set_cpp_20("ExampleList")
set_debug_mode("ExampleList")