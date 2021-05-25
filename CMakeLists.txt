cmake_minimum_required(VERSION 3.19)
project(pslightdash VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SourceFiles "${CMAKE_CURRENT_LIST_DIR}/src/*")
set(PSLIGHTDASH_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include/")
add_executable(pslightdash ${SourceFiles})
include_directories(pslightdash ${PSLIGHTDASH_INCLUDE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(pslightdash PRIVATE glfw)

add_custom_command(TARGET pslightdash PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res/ $<TARGET_FILE_DIR:pslightdash>/res/)

configure_file("include/pslightdashconfig.h.in" "../include/pslightdashconfig.h")

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/FS)
endif ()