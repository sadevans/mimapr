# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/n1shko/hw/mimapr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/n1shko/hw/mimapr

# Include any dependencies generated for this target.
include CMakeFiles/mimapr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mimapr.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mimapr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mimapr.dir/flags.make

CMakeFiles/mimapr.dir/lab.cpp.o: CMakeFiles/mimapr.dir/flags.make
CMakeFiles/mimapr.dir/lab.cpp.o: lab.cpp
CMakeFiles/mimapr.dir/lab.cpp.o: CMakeFiles/mimapr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/n1shko/hw/mimapr/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mimapr.dir/lab.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mimapr.dir/lab.cpp.o -MF CMakeFiles/mimapr.dir/lab.cpp.o.d -o CMakeFiles/mimapr.dir/lab.cpp.o -c /home/n1shko/hw/mimapr/lab.cpp

CMakeFiles/mimapr.dir/lab.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mimapr.dir/lab.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/n1shko/hw/mimapr/lab.cpp > CMakeFiles/mimapr.dir/lab.cpp.i

CMakeFiles/mimapr.dir/lab.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mimapr.dir/lab.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/n1shko/hw/mimapr/lab.cpp -o CMakeFiles/mimapr.dir/lab.cpp.s

# Object files for target mimapr
mimapr_OBJECTS = \
"CMakeFiles/mimapr.dir/lab.cpp.o"

# External object files for target mimapr
mimapr_EXTERNAL_OBJECTS =

mimapr: CMakeFiles/mimapr.dir/lab.cpp.o
mimapr: CMakeFiles/mimapr.dir/build.make
mimapr: CMakeFiles/mimapr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/n1shko/hw/mimapr/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mimapr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mimapr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mimapr.dir/build: mimapr
.PHONY : CMakeFiles/mimapr.dir/build

CMakeFiles/mimapr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mimapr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mimapr.dir/clean

CMakeFiles/mimapr.dir/depend:
	cd /home/n1shko/hw/mimapr && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/n1shko/hw/mimapr /home/n1shko/hw/mimapr /home/n1shko/hw/mimapr /home/n1shko/hw/mimapr /home/n1shko/hw/mimapr/CMakeFiles/mimapr.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/mimapr.dir/depend
