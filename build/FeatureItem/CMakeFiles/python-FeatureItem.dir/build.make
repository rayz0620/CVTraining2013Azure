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
include FeatureItem/CMakeFiles/python-FeatureItem.dir/depend.make

# Include the progress variables for this target.
include FeatureItem/CMakeFiles/python-FeatureItem.dir/progress.make

# Include the compile flags for this target's objects.
include FeatureItem/CMakeFiles/python-FeatureItem.dir/flags.make

FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o: FeatureItem/CMakeFiles/python-FeatureItem.dir/flags.make
FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o: ../FeatureItem/src/python-FeatureItem.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rayz/github/CVTraining2013Azure/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o"
	cd /home/rayz/github/CVTraining2013Azure/build/FeatureItem && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o -c /home/rayz/github/CVTraining2013Azure/FeatureItem/src/python-FeatureItem.cpp

FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.i"
	cd /home/rayz/github/CVTraining2013Azure/build/FeatureItem && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rayz/github/CVTraining2013Azure/FeatureItem/src/python-FeatureItem.cpp > CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.i

FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.s"
	cd /home/rayz/github/CVTraining2013Azure/build/FeatureItem && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rayz/github/CVTraining2013Azure/FeatureItem/src/python-FeatureItem.cpp -o CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.s

FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.requires:
.PHONY : FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.requires

FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.provides: FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.requires
	$(MAKE) -f FeatureItem/CMakeFiles/python-FeatureItem.dir/build.make FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.provides.build
.PHONY : FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.provides

FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.provides.build: FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o

# Object files for target python-FeatureItem
python__FeatureItem_OBJECTS = \
"CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o"

# External object files for target python-FeatureItem
python__FeatureItem_EXTERNAL_OBJECTS =

FeatureItem/lib/FeatureItem.so: FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o
FeatureItem/lib/FeatureItem.so: FeatureItem/CMakeFiles/python-FeatureItem.dir/build.make
FeatureItem/lib/FeatureItem.so: FeatureItem/lib/libFeatureItem.a
FeatureItem/lib/FeatureItem.so: IOUtils/lib/libIOUtils.a
FeatureItem/lib/FeatureItem.so: /usr/local/lib/libboost_python.so
FeatureItem/lib/FeatureItem.so: /usr/local/lib/libboost_thread.so
FeatureItem/lib/FeatureItem.so: /usr/local/lib/libboost_filesystem.so
FeatureItem/lib/FeatureItem.so: /usr/local/lib/libboost_system.so
FeatureItem/lib/FeatureItem.so: /usr/lib/x86_64-linux-gnu/libpython2.7.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_calib3d.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_contrib.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_core.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_features2d.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_flann.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_highgui.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_imgproc.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_legacy.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_ml.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_objdetect.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_photo.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_stitching.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_ts.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_video.so
FeatureItem/lib/FeatureItem.so: /usr/lib/libopencv_videostab.so
FeatureItem/lib/FeatureItem.so: FeatureItem/CMakeFiles/python-FeatureItem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module lib/FeatureItem.so"
	cd /home/rayz/github/CVTraining2013Azure/build/FeatureItem && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/python-FeatureItem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
FeatureItem/CMakeFiles/python-FeatureItem.dir/build: FeatureItem/lib/FeatureItem.so
.PHONY : FeatureItem/CMakeFiles/python-FeatureItem.dir/build

FeatureItem/CMakeFiles/python-FeatureItem.dir/requires: FeatureItem/CMakeFiles/python-FeatureItem.dir/src/python-FeatureItem.cpp.o.requires
.PHONY : FeatureItem/CMakeFiles/python-FeatureItem.dir/requires

FeatureItem/CMakeFiles/python-FeatureItem.dir/clean:
	cd /home/rayz/github/CVTraining2013Azure/build/FeatureItem && $(CMAKE_COMMAND) -P CMakeFiles/python-FeatureItem.dir/cmake_clean.cmake
.PHONY : FeatureItem/CMakeFiles/python-FeatureItem.dir/clean

FeatureItem/CMakeFiles/python-FeatureItem.dir/depend:
	cd /home/rayz/github/CVTraining2013Azure/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rayz/github/CVTraining2013Azure /home/rayz/github/CVTraining2013Azure/FeatureItem /home/rayz/github/CVTraining2013Azure/build /home/rayz/github/CVTraining2013Azure/build/FeatureItem /home/rayz/github/CVTraining2013Azure/build/FeatureItem/CMakeFiles/python-FeatureItem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : FeatureItem/CMakeFiles/python-FeatureItem.dir/depend

