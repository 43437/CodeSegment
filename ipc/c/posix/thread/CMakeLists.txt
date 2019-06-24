cmake_minimum_required(VERSION 2.8)

project(ipc)

set(CMAKE_BUILD_TYPE Debug)

add_executable(thread_simple 
thread_simple.c
err_handle.c
)

target_link_libraries(thread_simple pthread)

add_executable(thread_clean 
thread_clean.c 
err_handle.c
)
target_link_libraries(thread_clean pthread)

add_executable(lock_timed 
lock_timed.c 
)
target_link_libraries(lock_timed pthread)

add_executable(lock_wrlock 
lock_wrlock.c 
err_handle.c
)
target_link_libraries(lock_wrlock pthread)

add_executable(lock_signal
lock_signal.c 
err_handle.c
)
target_link_libraries(lock_signal pthread)

add_executable(lock_simple
lock_simple.c 
err_handle.c
)
target_link_libraries(lock_simple pthread)

add_executable(lock_double
lock_double.c 
err_handle.c
)
target_link_libraries(lock_double pthread)