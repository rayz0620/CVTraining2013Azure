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
include SemanticDatabase/CMakeFiles/SemanticDatabase.dir/depend.make

# Include the progress variables for this target.
include SemanticDatabase/CMakeFiles/SemanticDatabase.dir/progress.make

# Include the compile flags for this target's objects.
include SemanticDatabase/CMakeFiles/SemanticDatabase.dir/flags.make

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o: SemanticDatabase/CMakeFiles/SemanticDatabase.dir/flags.make
SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o: ../SemanticDatabase/src/SemanticDatabase.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rayz/github/CVTraining2013Azure/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o"
	cd /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o -c /home/rayz/github/CVTraining2013Azure/SemanticDatabase/src/SemanticDatabase.cpp

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.i"
	cd /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rayz/github/CVTraining2013Azure/SemanticDatabase/src/SemanticDatabase.cpp > CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.i

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.s"
	cd /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rayz/github/CVTraining2013Azure/SemanticDatabase/src/SemanticDatabase.cpp -o CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.s

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.requires:
.PHONY : SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.requires

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.provides: SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.requires
	$(MAKE) -f SemanticDatabase/CMakeFiles/SemanticDatabase.dir/build.make SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.provides.build
.PHONY : SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.provides

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.provides.build: SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o

# Object files for target SemanticDatabase
SemanticDatabase_OBJECTS = \
"CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o"

# External object files for target SemanticDatabase
SemanticDatabase_EXTERNAL_OBJECTS =

SemanticDatabase/lib/libSemanticDatabase.a: SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o
SemanticDatabase/lib/libSemanticDatabase.a: SemanticDatabase/CMakeFiles/SemanticDatabase.dir/build.make
SemanticDatabase/lib/libSemanticDatabase.a: SemanticDatabase/CMakeFiles/SemanticDatabase.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library lib/libSemanticDatabase.a"
	cd /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase && $(CMAKE_COMMAND) -P CMakeFiles/SemanticDatabase.dir/cmake_clean_target.cmake
	cd /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SemanticDatabase.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SemanticDatabase/CMakeFiles/SemanticDatabase.dir/build: SemanticDatabase/lib/libSemanticDatabase.a
.PHONY : SemanticDatabase/CMakeFiles/SemanticDatabase.dir/build

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/requires: SemanticDatabase/CMakeFiles/SemanticDatabase.dir/src/SemanticDatabase.cpp.o.requires
.PHONY : SemanticDatabase/CMakeFiles/SemanticDatabase.dir/requires

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/clean:
	cd /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase && $(CMAKE_COMMAND) -P CMakeFiles/SemanticDatabase.dir/cmake_clean.cmake
.PHONY : SemanticDatabase/CMakeFiles/SemanticDatabase.dir/clean

SemanticDatabase/CMakeFiles/SemanticDatabase.dir/depend:
	cd /home/rayz/github/CVTraining2013Azure/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rayz/github/CVTraining2013Azure /home/rayz/github/CVTraining2013Azure/SemanticDatabase /home/rayz/github/CVTraining2013Azure/build /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase /home/rayz/github/CVTraining2013Azure/build/SemanticDatabase/CMakeFiles/SemanticDatabase.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SemanticDatabase/CMakeFiles/SemanticDatabase.dir/depend

