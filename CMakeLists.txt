cmake_minimum_required(VERSION 3.20)
project(smart_note C)

set(CMAKE_C_STANDARD 99)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(smart_note main.c)
