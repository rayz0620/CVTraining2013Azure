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
include CMakeFiles/sift.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sift.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sift.dir/flags.make

CMakeFiles/sift.dir/src/python-sift.cpp.o: CMakeFiles/sift.dir/flags.make
CMakeFiles/sift.dir/src/python-sift.cpp.o: ../src/python-sift.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rayz/projectsc/Python-SIFT/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sift.dir/src/python-sift.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sift.dir/src/python-sift.cpp.o -c /home/rayz/projectsc/Python-SIFT/src/python-sift.cpp

CMakeFiles/sift.dir/src/python-sift.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sift.dir/src/python-sift.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rayz/projectsc/Python-SIFT/src/python-sift.cpp > CMakeFiles/sift.dir/src/python-sift.cpp.i

CMakeFiles/sift.dir/src/python-sift.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sift.dir/src/python-sift.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rayz/projectsc/Python-SIFT/src/python-sift.cpp -o CMakeFiles/sift.dir/src/python-sift.cpp.s

CMakeFiles/sift.dir/src/python-sift.cpp.o.requires:
.PHONY : CMakeFiles/sift.dir/src/python-sift.cpp.o.requires

CMakeFiles/sift.dir/src/python-sift.cpp.o.provides: CMakeFiles/sift.dir/src/python-sift.cpp.o.requires
	$(MAKE) -f CMakeFiles/sift.dir/build.make CMakeFiles/sift.dir/src/python-sift.cpp.o.provides.build
.PHONY : CMakeFiles/sift.dir/src/python-sift.cpp.o.provides

CMakeFiles/sift.dir/src/python-sift.cpp.o.provides.build: CMakeFiles/sift.dir/src/python-sift.cpp.o

# Object files for target sift
sift_OBJECTS = \
"CMakeFiles/sift.dir/src/python-sift.cpp.o"

# External object files for target sift
sift_EXTERNAL_OBJECTS =

lib/sift.so: CMakeFiles/sift.dir/src/python-sift.cpp.o
lib/sift.so: CMakeFiles/sift.dir/build.make
lib/sift.so: /usr/local/lib/libboost_python.so
lib/sift.so: /usr/lib/x86_64-linux-gnu/libpython2.7.so
lib/sift.so: /usr/lib/libopencv_calib3d.so
lib/sift.so: /usr/lib/libopencv_contrib.so
lib/sift.so: /usr/lib/libopencv_core.so
lib/sift.so: /usr/lib/libopencv_features2d.so
lib/sift.so: /usr/lib/libopencv_flann.so
lib/sift.so: /usr/lib/libopencv_highgui.so
lib/sift.so: /usr/lib/libopencv_imgproc.so
lib/sift.so: /usr/lib/libopencv_legacy.so
lib/sift.so: /usr/lib/libopencv_ml.so
lib/sift.so: /usr/lib/libopencv_objdetect.so
lib/sift.so: /usr/lib/libopencv_photo.so
lib/sift.so: /usr/lib/libopencv_stitching.so
lib/sift.so: /usr/lib/libopencv_ts.so
lib/sift.so: /usr/lib/libopencv_video.so
lib/sift.so: /usr/lib/libopencv_videostab.so
lib/sift.so: CMakeFiles/sift.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module lib/sift.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sift.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sift.dir/build: lib/sift.so
.PHONY : CMakeFiles/sift.dir/build

CMakeFiles/sift.dir/requires: CMakeFiles/sift.dir/src/python-sift.cpp.o.requires
.PHONY : CMakeFiles/sift.dir/requires

CMakeFiles/sift.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sift.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sift.dir/clean

CMakeFiles/sift.dir/depend:
	cd /home/rayz/projectsc/Python-SIFT/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rayz/projectsc/Python-SIFT /home/rayz/projectsc/Python-SIFT /home/rayz/projectsc/Python-SIFT/build /home/rayz/projectsc/Python-SIFT/build /home/rayz/projectsc/Python-SIFT/build/CMakeFiles/sift.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sift.dir/depend

