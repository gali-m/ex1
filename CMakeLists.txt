cmake_minimum_required(VERSION 3.0.0)

project(ex1 VERSION 0.1.0 LANGUAGES C)

set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})
<<<<<<< HEAD
link_directories(.)
add_executable(ex1 date.c priority_queue.c events_pq_helper.c members_pq_helper.c event_manager.c event_manager_example_tests.c) 
target_link_libraries(ex1 libpriority_queue.a)
=======

<<<<<<< HEAD
add_executable(ex1 date.c date_tests.c) 
=======
# add_executable(ex1_queue priority_queue.c pq_example_tests.c) 
add_executable(ex1_queue priority_queue.c test_online.c pq_helper.c) 
>>>>>>> priority_queue
>>>>>>> 24e42aecb3bb70d27b3a2ca48ebdf2dfec73dc3a
