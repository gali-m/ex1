# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gali/mtm/ex1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gali/mtm/ex1/build

# Include any dependencies generated for this target.
include CMakeFiles/ex1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex1.dir/flags.make

CMakeFiles/ex1.dir/date.c.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/date.c.o: ../date.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ex1.dir/date.c.o"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex1.dir/date.c.o   -c /home/gali/mtm/ex1/date.c

CMakeFiles/ex1.dir/date.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex1.dir/date.c.i"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gali/mtm/ex1/date.c > CMakeFiles/ex1.dir/date.c.i

CMakeFiles/ex1.dir/date.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex1.dir/date.c.s"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gali/mtm/ex1/date.c -o CMakeFiles/ex1.dir/date.c.s

CMakeFiles/ex1.dir/pq_helper.c.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/pq_helper.c.o: ../pq_helper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ex1.dir/pq_helper.c.o"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex1.dir/pq_helper.c.o   -c /home/gali/mtm/ex1/pq_helper.c

CMakeFiles/ex1.dir/pq_helper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex1.dir/pq_helper.c.i"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gali/mtm/ex1/pq_helper.c > CMakeFiles/ex1.dir/pq_helper.c.i

CMakeFiles/ex1.dir/pq_helper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex1.dir/pq_helper.c.s"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gali/mtm/ex1/pq_helper.c -o CMakeFiles/ex1.dir/pq_helper.c.s

CMakeFiles/ex1.dir/priority_queue.c.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/priority_queue.c.o: ../priority_queue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ex1.dir/priority_queue.c.o"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex1.dir/priority_queue.c.o   -c /home/gali/mtm/ex1/priority_queue.c

CMakeFiles/ex1.dir/priority_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex1.dir/priority_queue.c.i"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gali/mtm/ex1/priority_queue.c > CMakeFiles/ex1.dir/priority_queue.c.i

CMakeFiles/ex1.dir/priority_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex1.dir/priority_queue.c.s"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gali/mtm/ex1/priority_queue.c -o CMakeFiles/ex1.dir/priority_queue.c.s

CMakeFiles/ex1.dir/events_pq_helper.c.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/events_pq_helper.c.o: ../events_pq_helper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ex1.dir/events_pq_helper.c.o"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex1.dir/events_pq_helper.c.o   -c /home/gali/mtm/ex1/events_pq_helper.c

CMakeFiles/ex1.dir/events_pq_helper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex1.dir/events_pq_helper.c.i"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gali/mtm/ex1/events_pq_helper.c > CMakeFiles/ex1.dir/events_pq_helper.c.i

CMakeFiles/ex1.dir/events_pq_helper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex1.dir/events_pq_helper.c.s"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gali/mtm/ex1/events_pq_helper.c -o CMakeFiles/ex1.dir/events_pq_helper.c.s

CMakeFiles/ex1.dir/members_pq_helper.c.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/members_pq_helper.c.o: ../members_pq_helper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ex1.dir/members_pq_helper.c.o"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex1.dir/members_pq_helper.c.o   -c /home/gali/mtm/ex1/members_pq_helper.c

CMakeFiles/ex1.dir/members_pq_helper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex1.dir/members_pq_helper.c.i"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gali/mtm/ex1/members_pq_helper.c > CMakeFiles/ex1.dir/members_pq_helper.c.i

CMakeFiles/ex1.dir/members_pq_helper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex1.dir/members_pq_helper.c.s"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gali/mtm/ex1/members_pq_helper.c -o CMakeFiles/ex1.dir/members_pq_helper.c.s

CMakeFiles/ex1.dir/event_manager.c.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/event_manager.c.o: ../event_manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ex1.dir/event_manager.c.o"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex1.dir/event_manager.c.o   -c /home/gali/mtm/ex1/event_manager.c

CMakeFiles/ex1.dir/event_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex1.dir/event_manager.c.i"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gali/mtm/ex1/event_manager.c > CMakeFiles/ex1.dir/event_manager.c.i

CMakeFiles/ex1.dir/event_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex1.dir/event_manager.c.s"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gali/mtm/ex1/event_manager.c -o CMakeFiles/ex1.dir/event_manager.c.s

CMakeFiles/ex1.dir/event_manager_example_tests.c.o: CMakeFiles/ex1.dir/flags.make
CMakeFiles/ex1.dir/event_manager_example_tests.c.o: ../event_manager_example_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/ex1.dir/event_manager_example_tests.c.o"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ex1.dir/event_manager_example_tests.c.o   -c /home/gali/mtm/ex1/event_manager_example_tests.c

CMakeFiles/ex1.dir/event_manager_example_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex1.dir/event_manager_example_tests.c.i"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gali/mtm/ex1/event_manager_example_tests.c > CMakeFiles/ex1.dir/event_manager_example_tests.c.i

CMakeFiles/ex1.dir/event_manager_example_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex1.dir/event_manager_example_tests.c.s"
	/usr/local/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gali/mtm/ex1/event_manager_example_tests.c -o CMakeFiles/ex1.dir/event_manager_example_tests.c.s

# Object files for target ex1
ex1_OBJECTS = \
"CMakeFiles/ex1.dir/date.c.o" \
"CMakeFiles/ex1.dir/pq_helper.c.o" \
"CMakeFiles/ex1.dir/priority_queue.c.o" \
"CMakeFiles/ex1.dir/events_pq_helper.c.o" \
"CMakeFiles/ex1.dir/members_pq_helper.c.o" \
"CMakeFiles/ex1.dir/event_manager.c.o" \
"CMakeFiles/ex1.dir/event_manager_example_tests.c.o"

# External object files for target ex1
ex1_EXTERNAL_OBJECTS =

ex1: CMakeFiles/ex1.dir/date.c.o
ex1: CMakeFiles/ex1.dir/pq_helper.c.o
ex1: CMakeFiles/ex1.dir/priority_queue.c.o
ex1: CMakeFiles/ex1.dir/events_pq_helper.c.o
ex1: CMakeFiles/ex1.dir/members_pq_helper.c.o
ex1: CMakeFiles/ex1.dir/event_manager.c.o
ex1: CMakeFiles/ex1.dir/event_manager_example_tests.c.o
ex1: CMakeFiles/ex1.dir/build.make
ex1: CMakeFiles/ex1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gali/mtm/ex1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable ex1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex1.dir/build: ex1

.PHONY : CMakeFiles/ex1.dir/build

CMakeFiles/ex1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex1.dir/clean

CMakeFiles/ex1.dir/depend:
	cd /home/gali/mtm/ex1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gali/mtm/ex1 /home/gali/mtm/ex1 /home/gali/mtm/ex1/build /home/gali/mtm/ex1/build /home/gali/mtm/ex1/build/CMakeFiles/ex1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex1.dir/depend

