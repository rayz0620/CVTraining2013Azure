# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/rayz/projectsc/Python-SIFT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rayz/projectsc/Python-SIFT/build

# Include any dependencies generated for this target.
include CMakeFiles/python-sift.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/python-sift.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/python-sift.dir/flags.make

CMakeFiles/python-sift.dir/src/python-sift.cpp.o: CMakeFiles/python-sift.dir/flags.make
CMakeFiles/python-sift.dir/src/python-sift.cpp.o: ../src/python-sift.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rayz/projectsc/Python-SIFT/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/python-sift.dir/src/python-sift.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/python-sift.dir/src/python-sift.cpp.o -c /home/rayz/projectsc/Python-SIFT/src/python-sift.cpp

CMakeFiles/python-sift.dir/src/python-sift.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/python-sift.dir/src/python-sift.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rayz/projectsc/Python-SIFT/src/python-sift.cpp > CMakeFiles/python-sift.dir/src/python-sift.cpp.i

CMakeFiles/python-sift.dir/src/python-sift.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/python-sift.dir/src/python-sift.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rayz/projectsc/Python-SIFT/src/python-sift.cpp -o CMakeFiles/python-sift.dir/src/python-sift.cpp.s

CMakeFiles/python-sift.dir/src/python-sift.cpp.o.requires:
.PHONY : CMakeFiles/python-sift.dir/src/python-sift.cpp.o.requires

CMakeFiles/python-sift.dir/src/python-sift.cpp.o.provides: CMakeFiles/python-sift.dir/src/python-sift.cpp.o.requires
	$(MAKE) -f CMakeFiles/python-sift.dir/build.make CMakeFiles/python-sift.dir/src/python-sift.cpp.o.provides.build
.PHONY : CMakeFiles/python-sift.dir/src/python-sift.cpp.o.provides

CMakeFiles/python-sift.dir/src/python-sift.cpp.o.provides.build: CMakeFiles/python-sift.dir/src/python-sift.cpp.o

# Object files for target python-sift
python__sift_OBJECTS = \
"CMakeFiles/python-sift.dir/src/python-sift.cpp.o"

# External object files for target python-sift
python__sift_EXTERNAL_OBJECTS =

lib/python-sift.so: CMakeFiles/python-sift.dir/src/python-sift.cpp.o
lib/python-sift.so: CMakeFiles/python-sift.dir/build.make
lib/python-sift.so: /usr/local/lib/libboost_python.so
lib/python-sift.so: /usr/lib/x86_64-linux-gnu/libpython2.7.so
lib/python-sift.so: CMakeFiles/python-sift.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module lib/python-sift.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/python-sift.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/python-sift.dir/build: lib/python-sift.so
.PHONY : CMakeFiles/python-sift.dir/build

CMakeFiles/python-sift.dir/requires: CMakeFiles/python-sift.dir/src/python-sift.cpp.o.requires
.PHONY : CMakeFiles/python-sift.dir/requires

CMakeFiles/python-sift.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/python-sift.dir/cmake_clean.cmake
.PHONY : CMakeFiles/python-sift.dir/clean

CMakeFiles/python-sift.dir/depend:
	cd /home/rayz/projectsc/Python-SIFT/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rayz/projectsc/Python-SIFT /home/rayz/projectsc/Python-SIFT /home/rayz/projectsc/Python-SIFT/build /home/rayz/projectsc/Python-SIFT/build /home/rayz/projectsc/Python-SIFT/build/CMakeFiles/python-sift.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/python-sift.dir/depend

