# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /root/workspace/test/ssd2xx-demo/4.littlevgl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/test/ssd2xx-demo/4.littlevgl

# Utility rule file for cp-lvgl.

# Include the progress variables for this target.
include CMakeFiles/cp-lvgl.dir/progress.make

CMakeFiles/cp-lvgl:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/root/workspace/test/ssd2xx-demo/4.littlevgl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "/usr/bin/cmake -E copy_directory /root/workspace/test/ssd2xx-demo/4.littlevgl/res /res/"
	/usr/bin/cmake -E make_directory /res/
	/usr/bin/cmake -E copy_directory /root/workspace/test/ssd2xx-demo/4.littlevgl/res/ /res/

cp-lvgl: CMakeFiles/cp-lvgl
cp-lvgl: CMakeFiles/cp-lvgl.dir/build.make

.PHONY : cp-lvgl

# Rule to build all files generated by this target.
CMakeFiles/cp-lvgl.dir/build: cp-lvgl

.PHONY : CMakeFiles/cp-lvgl.dir/build

CMakeFiles/cp-lvgl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cp-lvgl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cp-lvgl.dir/clean

CMakeFiles/cp-lvgl.dir/depend:
	cd /root/workspace/test/ssd2xx-demo/4.littlevgl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/test/ssd2xx-demo/4.littlevgl /root/workspace/test/ssd2xx-demo/4.littlevgl /root/workspace/test/ssd2xx-demo/4.littlevgl /root/workspace/test/ssd2xx-demo/4.littlevgl /root/workspace/test/ssd2xx-demo/4.littlevgl/CMakeFiles/cp-lvgl.dir/DependInfo.cmake
.PHONY : CMakeFiles/cp-lvgl.dir/depend

