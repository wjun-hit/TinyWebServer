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
include src/utils/CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include src/utils/CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include src/utils/CMakeFiles/utils.dir/flags.make

src/utils/CMakeFiles/utils.dir/ExactTime.cpp.o: src/utils/CMakeFiles/utils.dir/flags.make
src/utils/CMakeFiles/utils.dir/ExactTime.cpp.o: ../src/utils/ExactTime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/utils/CMakeFiles/utils.dir/ExactTime.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/utils && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/ExactTime.cpp.o -c /home/wjun/code/tinyWeb/src/utils/ExactTime.cpp

src/utils/CMakeFiles/utils.dir/ExactTime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/ExactTime.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/utils && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/utils/ExactTime.cpp > CMakeFiles/utils.dir/ExactTime.cpp.i

src/utils/CMakeFiles/utils.dir/ExactTime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/ExactTime.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/utils && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/utils/ExactTime.cpp -o CMakeFiles/utils.dir/ExactTime.cpp.s

# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/ExactTime.cpp.o"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

lib/libutils.a: src/utils/CMakeFiles/utils.dir/ExactTime.cpp.o
lib/libutils.a: src/utils/CMakeFiles/utils.dir/build.make
lib/libutils.a: src/utils/CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libutils.a"
	cd /home/wjun/code/tinyWeb/build/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean_target.cmake
	cd /home/wjun/code/tinyWeb/build/src/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/utils/CMakeFiles/utils.dir/build: lib/libutils.a

.PHONY : src/utils/CMakeFiles/utils.dir/build

src/utils/CMakeFiles/utils.dir/clean:
	cd /home/wjun/code/tinyWeb/build/src/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : src/utils/CMakeFiles/utils.dir/clean

src/utils/CMakeFiles/utils.dir/depend:
	cd /home/wjun/code/tinyWeb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjun/code/tinyWeb /home/wjun/code/tinyWeb/src/utils /home/wjun/code/tinyWeb/build /home/wjun/code/tinyWeb/build/src/utils /home/wjun/code/tinyWeb/build/src/utils/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/utils/CMakeFiles/utils.dir/depend

