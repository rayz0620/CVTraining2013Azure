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
CMAKE_SOURCE_DIR = /home/rayz/projectsc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rayz/projectsc/build

# Include any dependencies generated for this target.
include SparseCoding/CMakeFiles/python-SparseCoding.dir/depend.make

# Include the progress variables for this target.
include SparseCoding/CMakeFiles/python-SparseCoding.dir/progress.make

# Include the compile flags for this target's objects.
include SparseCoding/CMakeFiles/python-SparseCoding.dir/flags.make

SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o: SparseCoding/CMakeFiles/python-SparseCoding.dir/flags.make
SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o: ../SparseCoding/src/python-SparseCoding.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rayz/projectsc/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o"
	cd /home/rayz/projectsc/build/SparseCoding && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o -c /home/rayz/projectsc/SparseCoding/src/python-SparseCoding.cpp

SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.i"
	cd /home/rayz/projectsc/build/SparseCoding && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rayz/projectsc/SparseCoding/src/python-SparseCoding.cpp > CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.i

SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.s"
	cd /home/rayz/projectsc/build/SparseCoding && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rayz/projectsc/SparseCoding/src/python-SparseCoding.cpp -o CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.s

SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.requires:
.PHONY : SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.requires

SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.provides: SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.requires
	$(MAKE) -f SparseCoding/CMakeFiles/python-SparseCoding.dir/build.make SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.provides.build
.PHONY : SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.provides

SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.provides.build: SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o

# Object files for target python-SparseCoding
python__SparseCoding_OBJECTS = \
"CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o"

# External object files for target python-SparseCoding
python__SparseCoding_EXTERNAL_OBJECTS =

SparseCoding/lib/SparseCoding.so: SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o
SparseCoding/lib/SparseCoding.so: SparseCoding/CMakeFiles/python-SparseCoding.dir/build.make
SparseCoding/lib/SparseCoding.so: /usr/local/lib/libboost_python.so
SparseCoding/lib/SparseCoding.so: /usr/lib/x86_64-linux-gnu/libpython2.7.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_calib3d.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_contrib.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_core.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_features2d.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_flann.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_highgui.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_imgproc.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_legacy.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_ml.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_objdetect.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_photo.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_stitching.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_ts.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_video.so
SparseCoding/lib/SparseCoding.so: /usr/lib/libopencv_videostab.so
SparseCoding/lib/SparseCoding.so: SparseCoding/lib/libSparseCoding.a
SparseCoding/lib/SparseCoding.so: MatrixUtils/lib/libMatrixUtils.a
SparseCoding/lib/SparseCoding.so: IOUtils/lib/libIOUtils.a
SparseCoding/lib/SparseCoding.so: SparseCoding/CMakeFiles/python-SparseCoding.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module lib/SparseCoding.so"
	cd /home/rayz/projectsc/build/SparseCoding && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/python-SparseCoding.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SparseCoding/CMakeFiles/python-SparseCoding.dir/build: SparseCoding/lib/SparseCoding.so
.PHONY : SparseCoding/CMakeFiles/python-SparseCoding.dir/build

SparseCoding/CMakeFiles/python-SparseCoding.dir/requires: SparseCoding/CMakeFiles/python-SparseCoding.dir/src/python-SparseCoding.cpp.o.requires
.PHONY : SparseCoding/CMakeFiles/python-SparseCoding.dir/requires

SparseCoding/CMakeFiles/python-SparseCoding.dir/clean:
	cd /home/rayz/projectsc/build/SparseCoding && $(CMAKE_COMMAND) -P CMakeFiles/python-SparseCoding.dir/cmake_clean.cmake
.PHONY : SparseCoding/CMakeFiles/python-SparseCoding.dir/clean

SparseCoding/CMakeFiles/python-SparseCoding.dir/depend:
	cd /home/rayz/projectsc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rayz/projectsc /home/rayz/projectsc/SparseCoding /home/rayz/projectsc/build /home/rayz/projectsc/build/SparseCoding /home/rayz/projectsc/build/SparseCoding/CMakeFiles/python-SparseCoding.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : SparseCoding/CMakeFiles/python-SparseCoding.dir/depend

