cmake_minimum_required(VERSION 3.12)

add_executable("ExampleVector" "${CMAKE_SOURCE_DIR}/example/ExampleVector.cpp")
target_include_directories("ExampleVector" PRIVATE "${CMAKE_SOURCE_DIR}/include/mini-stl")
target_link_libraries("ExampleVector" INTERFACE "mini-stl")
set_cpp_20("ExampleVector")
set_debug_mode("ExampleVector")