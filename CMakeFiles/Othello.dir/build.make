# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rickard/CLionProjects/Othello

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rickard/CLionProjects/Othello

# Include any dependencies generated for this target.
include CMakeFiles/Othello.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Othello.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Othello.dir/flags.make

CMakeFiles/Othello.dir/agent.cpp.o: CMakeFiles/Othello.dir/flags.make
CMakeFiles/Othello.dir/agent.cpp.o: agent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rickard/CLionProjects/Othello/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Othello.dir/agent.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Othello.dir/agent.cpp.o -c /Users/rickard/CLionProjects/Othello/agent.cpp

CMakeFiles/Othello.dir/agent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Othello.dir/agent.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rickard/CLionProjects/Othello/agent.cpp > CMakeFiles/Othello.dir/agent.cpp.i

CMakeFiles/Othello.dir/agent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Othello.dir/agent.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rickard/CLionProjects/Othello/agent.cpp -o CMakeFiles/Othello.dir/agent.cpp.s

# Object files for target Othello
Othello_OBJECTS = \
"CMakeFiles/Othello.dir/agent.cpp.o"

# External object files for target Othello
Othello_EXTERNAL_OBJECTS =

Othello: CMakeFiles/Othello.dir/agent.cpp.o
Othello: CMakeFiles/Othello.dir/build.make
Othello: CMakeFiles/Othello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rickard/CLionProjects/Othello/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Othello"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Othello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Othello.dir/build: Othello

.PHONY : CMakeFiles/Othello.dir/build

CMakeFiles/Othello.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Othello.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Othello.dir/clean

CMakeFiles/Othello.dir/depend:
	cd /Users/rickard/CLionProjects/Othello && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rickard/CLionProjects/Othello /Users/rickard/CLionProjects/Othello /Users/rickard/CLionProjects/Othello /Users/rickard/CLionProjects/Othello /Users/rickard/CLionProjects/Othello/CMakeFiles/Othello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Othello.dir/depend

