cmake_minimum_required( VERSION 3.12 )

add_executable("Test" "TestVector/TestVector.cpp" "TestList/TestList.cpp")

target_include_directories("Test" PRIVATE "${CMAKE_SOURCE_DIR}/include/mini-stl")
target_link_libraries("Test" INTERFACE "mini-stl")
set_cpp_20("Test")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries("Test" PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests("Test")