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
CMAKE_SOURCE_DIR = /home/rayz/github/CVTraining2013Azure

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rayz/github/CVTraining2013Azure/build

# Include any dependencies generated for this target.
include SIFT/CMakeFiles/SIFT.dir/depend.make

# Include the progress variables for this target.
include SIFT/CMakeFiles/SIFT.dir/progress.make

# Include the compile flags for this target's objects.
include SIFT/CMakeFiles/SIFT.dir/flags.make

SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o: SIFT/CMakeFiles/SIFT.dir/flags.make
SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o: ../SIFT/src/SIFT.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rayz/github/CVTraining2013Azure/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o"
	cd /home/rayz/github/CVTraining2013Azure/build/SIFT && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/SIFT.dir/src/SIFT.cpp.o -c /home/rayz/github/CVTraining2013Azure/SIFT/src/SIFT.cpp

SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SIFT.dir/src/SIFT.cpp.i"
	cd /home/rayz/github/CVTraining2013Azure/build/SIFT && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rayz/github/CVTraining2013Azure/SIFT/src/SIFT.cpp > CMakeFiles/SIFT.dir/src/SIFT.cpp.i

SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SIFT.dir/src/SIFT.cpp.s"
	cd /home/rayz/github/CVTraining2013Azure/build/SIFT && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rayz/github/CVTraining2013Azure/SIFT/src/SIFT.cpp -o CMakeFiles/SIFT.dir/src/SIFT.cpp.s

SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.requires:
.PHONY : SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.requires

SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.provides: SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.requires
	$(MAKE) -f SIFT/CMakeFiles/SIFT.dir/build.make SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.provides.build
.PHONY : SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.provides

SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.provides.build: SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o

# Object files for target SIFT
SIFT_OBJECTS = \
"CMakeFiles/SIFT.dir/src/SIFT.cpp.o"

# External object files for target SIFT
SIFT_EXTERNAL_OBJECTS =

SIFT/lib/libSIFT.a: SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o
SIFT/lib/libSIFT.a: SIFT/CMakeFiles/SIFT.dir/build.make
SIFT/lib/libSIFT.a: SIFT/CMakeFiles/SIFT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library lib/libSIFT.a"
	cd /home/rayz/github/CVTraining2013Azure/build/SIFT && $(CMAKE_COMMAND) -P CMakeFiles/SIFT.dir/cmake_clean_target.cmake
	cd /home/rayz/github/CVTraining2013Azure/build/SIFT && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SIFT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SIFT/CMakeFiles/SIFT.dir/build: SIFT/lib/libSIFT.a
.PHONY : SIFT/CMakeFiles/SIFT.dir/build

SIFT/CMakeFiles/SIFT.dir/requires: SIFT/CMakeFiles/SIFT.dir/src/SIFT.cpp.o.requires
.PHONY : SIFT/CMakeFiles/SIFT.dir/requires

SIFT/CMakeFiles/SIFT.dir/clean:
	cd /home/rayz/github/CVTraining2013Azure/build/SIFT && $(CMAKE_COMMAND) -P CMakeFiles/SIFT.dir/cmake_clean.cmake
.PHONY : SIFT/CMakeFiles/SIFT.dir/clean

SIFT/CMakeFiles/SIFT.dir/depend:
	cd /home/rayz/github/CVTraining2013Azure/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rayz/github/CVTraining2013Azure /home/rayz/github/CVTraining2013Azure/SIFT /home/rayz/github/CVTraining2013Azure/build /home/rayz/github/CVTraining2013Azure/build/SIFT /home/rayz/github/CVTraining2013Azure/build/SIFT/CMakeFiles/SIFT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SIFT/CMakeFiles/SIFT.dir/depend

