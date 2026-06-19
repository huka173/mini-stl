cmake_minimum_required (VERSION 3.8)

project("mini-stl")

add_executable(mini-stl "src/Main.cpp" "src/Vector/Vector.inl")

target_include_directories(mini-stl PRIVATE src)

set_target_properties(mini-stl PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if (MSVC)
    target_compile_options(mini-stl PRIVATE /W4 /permissive-)
else()
    target_compile_options(mini-stl PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(MSVC)
    target_compile_options(mini-stl PRIVATE
        $<$<CONFIG:Debug>:/fsanitize=address>
    )
    target_link_options(mini-stl PRIVATE
        $<$<CONFIG:Debug>:/fsanitize=address>
    )
else()
    target_compile_options(mini-stl PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fsanitize=undefined>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        $<$<CONFIG:Debug>:-g>
    )
    target_link_options(mini-stl PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fsanitize=undefined>
    )
endif()