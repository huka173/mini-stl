function(set_debug_mode target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()

    if(MSVC)
        target_compile_options(${target} PRIVATE
            $<$<CONFIG:Debug>:/fsanitize=address>
        )
        target_link_options(${target} PRIVATE
            $<$<CONFIG:Debug>:/fsanitize=address>
        )
    else()
        target_compile_options(${target} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address>
            $<$<CONFIG:Debug>:-fsanitize=undefined>
            $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
            $<$<CONFIG:Debug>:-g>
        )
        target_link_options(${target} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address>
            $<$<CONFIG:Debug>:-fsanitize=undefined>
        )
    endif()
endfunction()

function(set_cpp_20 target)
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
endfunction()

cmake_minimum_required (VERSION 3.12)

project("mini-stl")

add_library("mini-stl" INTERFACE)
target_include_directories("mini-stl" INTERFACE "${CMAKE_SOURCE_DIR}/include/mini-stl/")
set_cpp_20("mini-stl")

add_subdirectory("example/ExampleVector")
add_subdirectory("example/ExampleList")
add_subdirectory("example/ExampleHashMap")

enable_testing()
add_subdirectory("tests")