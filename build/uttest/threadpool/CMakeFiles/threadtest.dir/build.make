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
include uttest/threadpool/CMakeFiles/threadtest.dir/depend.make

# Include the progress variables for this target.
include uttest/threadpool/CMakeFiles/threadtest.dir/progress.make

# Include the compile flags for this target's objects.
include uttest/threadpool/CMakeFiles/threadtest.dir/flags.make

uttest/threadpool/CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.o: uttest/threadpool/CMakeFiles/threadtest.dir/flags.make
uttest/threadpool/CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.o: ../uttest/threadpool/ThreadPoolTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object uttest/threadpool/CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.o"
	cd /home/wjun/code/tinyWeb/build/uttest/threadpool && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.o -c /home/wjun/code/tinyWeb/uttest/threadpool/ThreadPoolTest.cpp

uttest/threadpool/CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.i"
	cd /home/wjun/code/tinyWeb/build/uttest/threadpool && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/uttest/threadpool/ThreadPoolTest.cpp > CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.i

uttest/threadpool/CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.s"
	cd /home/wjun/code/tinyWeb/build/uttest/threadpool && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/uttest/threadpool/ThreadPoolTest.cpp -o CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.s

# Object files for target threadtest
threadtest_OBJECTS = \
"CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.o"

# External object files for target threadtest
threadtest_EXTERNAL_OBJECTS =

threadtest: uttest/threadpool/CMakeFiles/threadtest.dir/ThreadPoolTest.cpp.o
threadtest: uttest/threadpool/CMakeFiles/threadtest.dir/build.make
threadtest: lib/libhttp.a
threadtest: lib/libutils.a
threadtest: lib/liblog.a
threadtest: uttest/threadpool/CMakeFiles/threadtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../threadtest"
	cd /home/wjun/code/tinyWeb/build/uttest/threadpool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threadtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
uttest/threadpool/CMakeFiles/threadtest.dir/build: threadtest

.PHONY : uttest/threadpool/CMakeFiles/threadtest.dir/build

uttest/threadpool/CMakeFiles/threadtest.dir/clean:
	cd /home/wjun/code/tinyWeb/build/uttest/threadpool && $(CMAKE_COMMAND) -P CMakeFiles/threadtest.dir/cmake_clean.cmake
.PHONY : uttest/threadpool/CMakeFiles/threadtest.dir/clean

uttest/threadpool/CMakeFiles/threadtest.dir/depend:
	cd /home/wjun/code/tinyWeb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjun/code/tinyWeb /home/wjun/code/tinyWeb/uttest/threadpool /home/wjun/code/tinyWeb/build /home/wjun/code/tinyWeb/build/uttest/threadpool /home/wjun/code/tinyWeb/build/uttest/threadpool/CMakeFiles/threadtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : uttest/threadpool/CMakeFiles/threadtest.dir/depend

