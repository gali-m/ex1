cmake_minimum_required(VERSION 3.0.0)

project(ex1 VERSION 0.1.0 LANGUAGES C)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})

<<<<<<< HEAD
add_executable(ex1 date.c date_tests.c) 
=======
# add_executable(ex1_queue priority_queue.c pq_example_tests.c) 
add_executable(ex1_queue priority_queue.c test_online.c pq_helper.c) 
>>>>>>> priority_queue
