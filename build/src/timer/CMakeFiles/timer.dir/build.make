# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wjun/code/tinyWeb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wjun/code/tinyWeb/build

# Include any dependencies generated for this target.
include src/timer/CMakeFiles/timer.dir/depend.make

# Include the progress variables for this target.
include src/timer/CMakeFiles/timer.dir/progress.make

# Include the compile flags for this target's objects.
include src/timer/CMakeFiles/timer.dir/flags.make

src/timer/CMakeFiles/timer.dir/Timed.cpp.o: src/timer/CMakeFiles/timer.dir/flags.make
src/timer/CMakeFiles/timer.dir/Timed.cpp.o: ../src/timer/Timed.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/timer/CMakeFiles/timer.dir/Timed.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/timer && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/timer.dir/Timed.cpp.o -c /home/wjun/code/tinyWeb/src/timer/Timed.cpp

src/timer/CMakeFiles/timer.dir/Timed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/timer.dir/Timed.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/timer && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/timer/Timed.cpp > CMakeFiles/timer.dir/Timed.cpp.i

src/timer/CMakeFiles/timer.dir/Timed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/timer.dir/Timed.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/timer && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/timer/Timed.cpp -o CMakeFiles/timer.dir/Timed.cpp.s

src/timer/CMakeFiles/timer.dir/TimedEvent.cpp.o: src/timer/CMakeFiles/timer.dir/flags.make
src/timer/CMakeFiles/timer.dir/TimedEvent.cpp.o: ../src/timer/TimedEvent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/timer/CMakeFiles/timer.dir/TimedEvent.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/timer && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/timer.dir/TimedEvent.cpp.o -c /home/wjun/code/tinyWeb/src/timer/TimedEvent.cpp

src/timer/CMakeFiles/timer.dir/TimedEvent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/timer.dir/TimedEvent.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/timer && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/timer/TimedEvent.cpp > CMakeFiles/timer.dir/TimedEvent.cpp.i

src/timer/CMakeFiles/timer.dir/TimedEvent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/timer.dir/TimedEvent.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/timer && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/timer/TimedEvent.cpp -o CMakeFiles/timer.dir/TimedEvent.cpp.s

# Object files for target timer
timer_OBJECTS = \
"CMakeFiles/timer.dir/Timed.cpp.o" \
"CMakeFiles/timer.dir/TimedEvent.cpp.o"

# External object files for target timer
timer_EXTERNAL_OBJECTS =

lib/libtimer.a: src/timer/CMakeFiles/timer.dir/Timed.cpp.o
lib/libtimer.a: src/timer/CMakeFiles/timer.dir/TimedEvent.cpp.o
lib/libtimer.a: src/timer/CMakeFiles/timer.dir/build.make
lib/libtimer.a: src/timer/CMakeFiles/timer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library ../../lib/libtimer.a"
	cd /home/wjun/code/tinyWeb/build/src/timer && $(CMAKE_COMMAND) -P CMakeFiles/timer.dir/cmake_clean_target.cmake
	cd /home/wjun/code/tinyWeb/build/src/timer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/timer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/timer/CMakeFiles/timer.dir/build: lib/libtimer.a

.PHONY : src/timer/CMakeFiles/timer.dir/build

src/timer/CMakeFiles/timer.dir/clean:
	cd /home/wjun/code/tinyWeb/build/src/timer && $(CMAKE_COMMAND) -P CMakeFiles/timer.dir/cmake_clean.cmake
.PHONY : src/timer/CMakeFiles/timer.dir/clean

src/timer/CMakeFiles/timer.dir/depend:
	cd /home/wjun/code/tinyWeb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjun/code/tinyWeb /home/wjun/code/tinyWeb/src/timer /home/wjun/code/tinyWeb/build /home/wjun/code/tinyWeb/build/src/timer /home/wjun/code/tinyWeb/build/src/timer/CMakeFiles/timer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/timer/CMakeFiles/timer.dir/depend

