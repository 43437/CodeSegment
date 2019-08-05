cmake_minimum_required(VERSION 2.8)

project(comm)

set(CMAKE_BUILD_TYPE Debug)

add_executable(process_simple
process_simple.c
err_handle.c
)

#target_link_libraries(process_simple)