# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jinzhengcai/Code/ellipse/CMakeFiles /home/jinzhengcai/Code/ellipse/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jinzhengcai/Code/ellipse/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named EllipseDetection

# Build rule for target.
EllipseDetection: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 EllipseDetection
.PHONY : EllipseDetection

# fast build rule for target.
EllipseDetection/fast:
	$(MAKE) -f CMakeFiles/EllipseDetection.dir/build.make CMakeFiles/EllipseDetection.dir/build
.PHONY : EllipseDetection/fast

#=============================================================================
# Target rules for targets named utils

# Build rule for target.
utils: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 utils
.PHONY : utils

# fast build rule for target.
utils/fast:
	$(MAKE) -f utils/CMakeFiles/utils.dir/build.make utils/CMakeFiles/utils.dir/build
.PHONY : utils/fast

EllipseDetection.o: EllipseDetection.cxx.o
.PHONY : EllipseDetection.o

# target to build an object file
EllipseDetection.cxx.o:
	$(MAKE) -f CMakeFiles/EllipseDetection.dir/build.make CMakeFiles/EllipseDetection.dir/EllipseDetection.cxx.o
.PHONY : EllipseDetection.cxx.o

EllipseDetection.i: EllipseDetection.cxx.i
.PHONY : EllipseDetection.i

# target to preprocess a source file
EllipseDetection.cxx.i:
	$(MAKE) -f CMakeFiles/EllipseDetection.dir/build.make CMakeFiles/EllipseDetection.dir/EllipseDetection.cxx.i
.PHONY : EllipseDetection.cxx.i

EllipseDetection.s: EllipseDetection.cxx.s
.PHONY : EllipseDetection.s

# target to generate assembly for a file
EllipseDetection.cxx.s:
	$(MAKE) -f CMakeFiles/EllipseDetection.dir/build.make CMakeFiles/EllipseDetection.dir/EllipseDetection.cxx.s
.PHONY : EllipseDetection.cxx.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... EllipseDetection"
	@echo "... utils"
	@echo "... EllipseDetection.o"
	@echo "... EllipseDetection.i"
	@echo "... EllipseDetection.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

