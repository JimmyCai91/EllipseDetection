# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jinzhengcai/Code/ellipse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jinzhengcai/Code/ellipse

# Include any dependencies generated for this target.
include utils/CMakeFiles/utils.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/utils.dir/flags.make

utils/CMakeFiles/utils.dir/preprocessing.cxx.o: utils/CMakeFiles/utils.dir/flags.make
utils/CMakeFiles/utils.dir/preprocessing.cxx.o: utils/preprocessing.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jinzhengcai/Code/ellipse/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object utils/CMakeFiles/utils.dir/preprocessing.cxx.o"
	cd /home/jinzhengcai/Code/ellipse/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/preprocessing.cxx.o -c /home/jinzhengcai/Code/ellipse/utils/preprocessing.cxx

utils/CMakeFiles/utils.dir/preprocessing.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/preprocessing.cxx.i"
	cd /home/jinzhengcai/Code/ellipse/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jinzhengcai/Code/ellipse/utils/preprocessing.cxx > CMakeFiles/utils.dir/preprocessing.cxx.i

utils/CMakeFiles/utils.dir/preprocessing.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/preprocessing.cxx.s"
	cd /home/jinzhengcai/Code/ellipse/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jinzhengcai/Code/ellipse/utils/preprocessing.cxx -o CMakeFiles/utils.dir/preprocessing.cxx.s

utils/CMakeFiles/utils.dir/preprocessing.cxx.o.requires:
.PHONY : utils/CMakeFiles/utils.dir/preprocessing.cxx.o.requires

utils/CMakeFiles/utils.dir/preprocessing.cxx.o.provides: utils/CMakeFiles/utils.dir/preprocessing.cxx.o.requires
	$(MAKE) -f utils/CMakeFiles/utils.dir/build.make utils/CMakeFiles/utils.dir/preprocessing.cxx.o.provides.build
.PHONY : utils/CMakeFiles/utils.dir/preprocessing.cxx.o.provides

utils/CMakeFiles/utils.dir/preprocessing.cxx.o.provides.build: utils/CMakeFiles/utils.dir/preprocessing.cxx.o

utils/CMakeFiles/utils.dir/fastpdist.cxx.o: utils/CMakeFiles/utils.dir/flags.make
utils/CMakeFiles/utils.dir/fastpdist.cxx.o: utils/fastpdist.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jinzhengcai/Code/ellipse/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object utils/CMakeFiles/utils.dir/fastpdist.cxx.o"
	cd /home/jinzhengcai/Code/ellipse/utils && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/utils.dir/fastpdist.cxx.o -c /home/jinzhengcai/Code/ellipse/utils/fastpdist.cxx

utils/CMakeFiles/utils.dir/fastpdist.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/fastpdist.cxx.i"
	cd /home/jinzhengcai/Code/ellipse/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/jinzhengcai/Code/ellipse/utils/fastpdist.cxx > CMakeFiles/utils.dir/fastpdist.cxx.i

utils/CMakeFiles/utils.dir/fastpdist.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/fastpdist.cxx.s"
	cd /home/jinzhengcai/Code/ellipse/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/jinzhengcai/Code/ellipse/utils/fastpdist.cxx -o CMakeFiles/utils.dir/fastpdist.cxx.s

utils/CMakeFiles/utils.dir/fastpdist.cxx.o.requires:
.PHONY : utils/CMakeFiles/utils.dir/fastpdist.cxx.o.requires

utils/CMakeFiles/utils.dir/fastpdist.cxx.o.provides: utils/CMakeFiles/utils.dir/fastpdist.cxx.o.requires
	$(MAKE) -f utils/CMakeFiles/utils.dir/build.make utils/CMakeFiles/utils.dir/fastpdist.cxx.o.provides.build
.PHONY : utils/CMakeFiles/utils.dir/fastpdist.cxx.o.provides

utils/CMakeFiles/utils.dir/fastpdist.cxx.o.provides.build: utils/CMakeFiles/utils.dir/fastpdist.cxx.o

# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/preprocessing.cxx.o" \
"CMakeFiles/utils.dir/fastpdist.cxx.o"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

utils/libutils.a: utils/CMakeFiles/utils.dir/preprocessing.cxx.o
utils/libutils.a: utils/CMakeFiles/utils.dir/fastpdist.cxx.o
utils/libutils.a: utils/CMakeFiles/utils.dir/build.make
utils/libutils.a: utils/CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libutils.a"
	cd /home/jinzhengcai/Code/ellipse/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean_target.cmake
	cd /home/jinzhengcai/Code/ellipse/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/utils.dir/build: utils/libutils.a
.PHONY : utils/CMakeFiles/utils.dir/build

utils/CMakeFiles/utils.dir/requires: utils/CMakeFiles/utils.dir/preprocessing.cxx.o.requires
utils/CMakeFiles/utils.dir/requires: utils/CMakeFiles/utils.dir/fastpdist.cxx.o.requires
.PHONY : utils/CMakeFiles/utils.dir/requires

utils/CMakeFiles/utils.dir/clean:
	cd /home/jinzhengcai/Code/ellipse/utils && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/utils.dir/clean

utils/CMakeFiles/utils.dir/depend:
	cd /home/jinzhengcai/Code/ellipse && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jinzhengcai/Code/ellipse /home/jinzhengcai/Code/ellipse/utils /home/jinzhengcai/Code/ellipse /home/jinzhengcai/Code/ellipse/utils /home/jinzhengcai/Code/ellipse/utils/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/utils.dir/depend

