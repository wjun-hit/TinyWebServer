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
include uttest/timer/CMakeFiles/timertest.dir/depend.make

# Include the progress variables for this target.
include uttest/timer/CMakeFiles/timertest.dir/progress.make

# Include the compile flags for this target's objects.
include uttest/timer/CMakeFiles/timertest.dir/flags.make

uttest/timer/CMakeFiles/timertest.dir/TimerTest.cpp.o: uttest/timer/CMakeFiles/timertest.dir/flags.make
uttest/timer/CMakeFiles/timertest.dir/TimerTest.cpp.o: ../uttest/timer/TimerTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object uttest/timer/CMakeFiles/timertest.dir/TimerTest.cpp.o"
	cd /home/wjun/code/tinyWeb/build/uttest/timer && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/timertest.dir/TimerTest.cpp.o -c /home/wjun/code/tinyWeb/uttest/timer/TimerTest.cpp

uttest/timer/CMakeFiles/timertest.dir/TimerTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/timertest.dir/TimerTest.cpp.i"
	cd /home/wjun/code/tinyWeb/build/uttest/timer && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/uttest/timer/TimerTest.cpp > CMakeFiles/timertest.dir/TimerTest.cpp.i

uttest/timer/CMakeFiles/timertest.dir/TimerTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/timertest.dir/TimerTest.cpp.s"
	cd /home/wjun/code/tinyWeb/build/uttest/timer && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/uttest/timer/TimerTest.cpp -o CMakeFiles/timertest.dir/TimerTest.cpp.s

# Object files for target timertest
timertest_OBJECTS = \
"CMakeFiles/timertest.dir/TimerTest.cpp.o"

# External object files for target timertest
timertest_EXTERNAL_OBJECTS =

timertest: uttest/timer/CMakeFiles/timertest.dir/TimerTest.cpp.o
timertest: uttest/timer/CMakeFiles/timertest.dir/build.make
timertest: lib/libhttp.a
timertest: lib/libutils.a
timertest: lib/liblog.a
timertest: uttest/timer/CMakeFiles/timertest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../timertest"
	cd /home/wjun/code/tinyWeb/build/uttest/timer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/timertest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
uttest/timer/CMakeFiles/timertest.dir/build: timertest

.PHONY : uttest/timer/CMakeFiles/timertest.dir/build

uttest/timer/CMakeFiles/timertest.dir/clean:
	cd /home/wjun/code/tinyWeb/build/uttest/timer && $(CMAKE_COMMAND) -P CMakeFiles/timertest.dir/cmake_clean.cmake
.PHONY : uttest/timer/CMakeFiles/timertest.dir/clean

uttest/timer/CMakeFiles/timertest.dir/depend:
	cd /home/wjun/code/tinyWeb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjun/code/tinyWeb /home/wjun/code/tinyWeb/uttest/timer /home/wjun/code/tinyWeb/build /home/wjun/code/tinyWeb/build/uttest/timer /home/wjun/code/tinyWeb/build/uttest/timer/CMakeFiles/timertest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : uttest/timer/CMakeFiles/timertest.dir/depend

