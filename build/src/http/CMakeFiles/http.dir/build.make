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
include src/http/CMakeFiles/http.dir/depend.make

# Include the progress variables for this target.
include src/http/CMakeFiles/http.dir/progress.make

# Include the compile flags for this target's objects.
include src/http/CMakeFiles/http.dir/flags.make

src/http/CMakeFiles/http.dir/HttpParse.cpp.o: src/http/CMakeFiles/http.dir/flags.make
src/http/CMakeFiles/http.dir/HttpParse.cpp.o: ../src/http/HttpParse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/http/CMakeFiles/http.dir/HttpParse.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/HttpParse.cpp.o -c /home/wjun/code/tinyWeb/src/http/HttpParse.cpp

src/http/CMakeFiles/http.dir/HttpParse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpParse.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/http/HttpParse.cpp > CMakeFiles/http.dir/HttpParse.cpp.i

src/http/CMakeFiles/http.dir/HttpParse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpParse.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/http/HttpParse.cpp -o CMakeFiles/http.dir/HttpParse.cpp.s

src/http/CMakeFiles/http.dir/HttpProcess.cpp.o: src/http/CMakeFiles/http.dir/flags.make
src/http/CMakeFiles/http.dir/HttpProcess.cpp.o: ../src/http/HttpProcess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/http/CMakeFiles/http.dir/HttpProcess.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/HttpProcess.cpp.o -c /home/wjun/code/tinyWeb/src/http/HttpProcess.cpp

src/http/CMakeFiles/http.dir/HttpProcess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpProcess.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/http/HttpProcess.cpp > CMakeFiles/http.dir/HttpProcess.cpp.i

src/http/CMakeFiles/http.dir/HttpProcess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpProcess.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/http/HttpProcess.cpp -o CMakeFiles/http.dir/HttpProcess.cpp.s

src/http/CMakeFiles/http.dir/HttpProduce.cpp.o: src/http/CMakeFiles/http.dir/flags.make
src/http/CMakeFiles/http.dir/HttpProduce.cpp.o: ../src/http/HttpProduce.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/http/CMakeFiles/http.dir/HttpProduce.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/HttpProduce.cpp.o -c /home/wjun/code/tinyWeb/src/http/HttpProduce.cpp

src/http/CMakeFiles/http.dir/HttpProduce.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpProduce.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/http/HttpProduce.cpp > CMakeFiles/http.dir/HttpProduce.cpp.i

src/http/CMakeFiles/http.dir/HttpProduce.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpProduce.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/http/HttpProduce.cpp -o CMakeFiles/http.dir/HttpProduce.cpp.s

src/http/CMakeFiles/http.dir/HttpReader.cpp.o: src/http/CMakeFiles/http.dir/flags.make
src/http/CMakeFiles/http.dir/HttpReader.cpp.o: ../src/http/HttpReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/http/CMakeFiles/http.dir/HttpReader.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/HttpReader.cpp.o -c /home/wjun/code/tinyWeb/src/http/HttpReader.cpp

src/http/CMakeFiles/http.dir/HttpReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpReader.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/http/HttpReader.cpp > CMakeFiles/http.dir/HttpReader.cpp.i

src/http/CMakeFiles/http.dir/HttpReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpReader.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/http/HttpReader.cpp -o CMakeFiles/http.dir/HttpReader.cpp.s

src/http/CMakeFiles/http.dir/HttpRequest.cpp.o: src/http/CMakeFiles/http.dir/flags.make
src/http/CMakeFiles/http.dir/HttpRequest.cpp.o: ../src/http/HttpRequest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/http/CMakeFiles/http.dir/HttpRequest.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/HttpRequest.cpp.o -c /home/wjun/code/tinyWeb/src/http/HttpRequest.cpp

src/http/CMakeFiles/http.dir/HttpRequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpRequest.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/http/HttpRequest.cpp > CMakeFiles/http.dir/HttpRequest.cpp.i

src/http/CMakeFiles/http.dir/HttpRequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpRequest.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/http/HttpRequest.cpp -o CMakeFiles/http.dir/HttpRequest.cpp.s

src/http/CMakeFiles/http.dir/HttpResponse.cpp.o: src/http/CMakeFiles/http.dir/flags.make
src/http/CMakeFiles/http.dir/HttpResponse.cpp.o: ../src/http/HttpResponse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/http/CMakeFiles/http.dir/HttpResponse.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/HttpResponse.cpp.o -c /home/wjun/code/tinyWeb/src/http/HttpResponse.cpp

src/http/CMakeFiles/http.dir/HttpResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpResponse.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/http/HttpResponse.cpp > CMakeFiles/http.dir/HttpResponse.cpp.i

src/http/CMakeFiles/http.dir/HttpResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpResponse.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/http/HttpResponse.cpp -o CMakeFiles/http.dir/HttpResponse.cpp.s

src/http/CMakeFiles/http.dir/HttpWriter.cpp.o: src/http/CMakeFiles/http.dir/flags.make
src/http/CMakeFiles/http.dir/HttpWriter.cpp.o: ../src/http/HttpWriter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/http/CMakeFiles/http.dir/HttpWriter.cpp.o"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http.dir/HttpWriter.cpp.o -c /home/wjun/code/tinyWeb/src/http/HttpWriter.cpp

src/http/CMakeFiles/http.dir/HttpWriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http.dir/HttpWriter.cpp.i"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjun/code/tinyWeb/src/http/HttpWriter.cpp > CMakeFiles/http.dir/HttpWriter.cpp.i

src/http/CMakeFiles/http.dir/HttpWriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http.dir/HttpWriter.cpp.s"
	cd /home/wjun/code/tinyWeb/build/src/http && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjun/code/tinyWeb/src/http/HttpWriter.cpp -o CMakeFiles/http.dir/HttpWriter.cpp.s

# Object files for target http
http_OBJECTS = \
"CMakeFiles/http.dir/HttpParse.cpp.o" \
"CMakeFiles/http.dir/HttpProcess.cpp.o" \
"CMakeFiles/http.dir/HttpProduce.cpp.o" \
"CMakeFiles/http.dir/HttpReader.cpp.o" \
"CMakeFiles/http.dir/HttpRequest.cpp.o" \
"CMakeFiles/http.dir/HttpResponse.cpp.o" \
"CMakeFiles/http.dir/HttpWriter.cpp.o"

# External object files for target http
http_EXTERNAL_OBJECTS =

lib/libhttp.a: src/http/CMakeFiles/http.dir/HttpParse.cpp.o
lib/libhttp.a: src/http/CMakeFiles/http.dir/HttpProcess.cpp.o
lib/libhttp.a: src/http/CMakeFiles/http.dir/HttpProduce.cpp.o
lib/libhttp.a: src/http/CMakeFiles/http.dir/HttpReader.cpp.o
lib/libhttp.a: src/http/CMakeFiles/http.dir/HttpRequest.cpp.o
lib/libhttp.a: src/http/CMakeFiles/http.dir/HttpResponse.cpp.o
lib/libhttp.a: src/http/CMakeFiles/http.dir/HttpWriter.cpp.o
lib/libhttp.a: src/http/CMakeFiles/http.dir/build.make
lib/libhttp.a: src/http/CMakeFiles/http.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjun/code/tinyWeb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library ../../lib/libhttp.a"
	cd /home/wjun/code/tinyWeb/build/src/http && $(CMAKE_COMMAND) -P CMakeFiles/http.dir/cmake_clean_target.cmake
	cd /home/wjun/code/tinyWeb/build/src/http && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/http/CMakeFiles/http.dir/build: lib/libhttp.a

.PHONY : src/http/CMakeFiles/http.dir/build

src/http/CMakeFiles/http.dir/clean:
	cd /home/wjun/code/tinyWeb/build/src/http && $(CMAKE_COMMAND) -P CMakeFiles/http.dir/cmake_clean.cmake
.PHONY : src/http/CMakeFiles/http.dir/clean

src/http/CMakeFiles/http.dir/depend:
	cd /home/wjun/code/tinyWeb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjun/code/tinyWeb /home/wjun/code/tinyWeb/src/http /home/wjun/code/tinyWeb/build /home/wjun/code/tinyWeb/build/src/http /home/wjun/code/tinyWeb/build/src/http/CMakeFiles/http.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/http/CMakeFiles/http.dir/depend
