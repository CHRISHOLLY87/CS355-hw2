# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/hw2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw2.dir/flags.make

CMakeFiles/hw2.dir/threads.c.o: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/threads.c.o: ../threads.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hw2.dir/threads.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hw2.dir/threads.c.o   -c "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/threads.c"

CMakeFiles/hw2.dir/threads.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hw2.dir/threads.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/threads.c" > CMakeFiles/hw2.dir/threads.c.i

CMakeFiles/hw2.dir/threads.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hw2.dir/threads.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/threads.c" -o CMakeFiles/hw2.dir/threads.c.s

CMakeFiles/hw2.dir/threads.c.o.requires:

.PHONY : CMakeFiles/hw2.dir/threads.c.o.requires

CMakeFiles/hw2.dir/threads.c.o.provides: CMakeFiles/hw2.dir/threads.c.o.requires
	$(MAKE) -f CMakeFiles/hw2.dir/build.make CMakeFiles/hw2.dir/threads.c.o.provides.build
.PHONY : CMakeFiles/hw2.dir/threads.c.o.provides

CMakeFiles/hw2.dir/threads.c.o.provides.build: CMakeFiles/hw2.dir/threads.c.o


CMakeFiles/hw2.dir/mysh.c.o: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/mysh.c.o: ../mysh.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hw2.dir/mysh.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hw2.dir/mysh.c.o   -c "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/mysh.c"

CMakeFiles/hw2.dir/mysh.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hw2.dir/mysh.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/mysh.c" > CMakeFiles/hw2.dir/mysh.c.i

CMakeFiles/hw2.dir/mysh.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hw2.dir/mysh.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/mysh.c" -o CMakeFiles/hw2.dir/mysh.c.s

CMakeFiles/hw2.dir/mysh.c.o.requires:

.PHONY : CMakeFiles/hw2.dir/mysh.c.o.requires

CMakeFiles/hw2.dir/mysh.c.o.provides: CMakeFiles/hw2.dir/mysh.c.o.requires
	$(MAKE) -f CMakeFiles/hw2.dir/build.make CMakeFiles/hw2.dir/mysh.c.o.provides.build
.PHONY : CMakeFiles/hw2.dir/mysh.c.o.provides

CMakeFiles/hw2.dir/mysh.c.o.provides.build: CMakeFiles/hw2.dir/mysh.c.o


CMakeFiles/hw2.dir/Lab01Part1.c.o: CMakeFiles/hw2.dir/flags.make
CMakeFiles/hw2.dir/Lab01Part1.c.o: ../Lab01Part1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/hw2.dir/Lab01Part1.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hw2.dir/Lab01Part1.c.o   -c "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/Lab01Part1.c"

CMakeFiles/hw2.dir/Lab01Part1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hw2.dir/Lab01Part1.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/Lab01Part1.c" > CMakeFiles/hw2.dir/Lab01Part1.c.i

CMakeFiles/hw2.dir/Lab01Part1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hw2.dir/Lab01Part1.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/Lab01Part1.c" -o CMakeFiles/hw2.dir/Lab01Part1.c.s

CMakeFiles/hw2.dir/Lab01Part1.c.o.requires:

.PHONY : CMakeFiles/hw2.dir/Lab01Part1.c.o.requires

CMakeFiles/hw2.dir/Lab01Part1.c.o.provides: CMakeFiles/hw2.dir/Lab01Part1.c.o.requires
	$(MAKE) -f CMakeFiles/hw2.dir/build.make CMakeFiles/hw2.dir/Lab01Part1.c.o.provides.build
.PHONY : CMakeFiles/hw2.dir/Lab01Part1.c.o.provides

CMakeFiles/hw2.dir/Lab01Part1.c.o.provides.build: CMakeFiles/hw2.dir/Lab01Part1.c.o


# Object files for target hw2
hw2_OBJECTS = \
"CMakeFiles/hw2.dir/threads.c.o" \
"CMakeFiles/hw2.dir/mysh.c.o" \
"CMakeFiles/hw2.dir/Lab01Part1.c.o"

# External object files for target hw2
hw2_EXTERNAL_OBJECTS =

hw2: CMakeFiles/hw2.dir/threads.c.o
hw2: CMakeFiles/hw2.dir/mysh.c.o
hw2: CMakeFiles/hw2.dir/Lab01Part1.c.o
hw2: CMakeFiles/hw2.dir/build.make
hw2: CMakeFiles/hw2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable hw2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw2.dir/build: hw2

.PHONY : CMakeFiles/hw2.dir/build

CMakeFiles/hw2.dir/requires: CMakeFiles/hw2.dir/threads.c.o.requires
CMakeFiles/hw2.dir/requires: CMakeFiles/hw2.dir/mysh.c.o.requires
CMakeFiles/hw2.dir/requires: CMakeFiles/hw2.dir/Lab01Part1.c.o.requires

.PHONY : CMakeFiles/hw2.dir/requires

CMakeFiles/hw2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw2.dir/clean

CMakeFiles/hw2.dir/depend:
	cd "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2" "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2" "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug" "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug" "/Users/Sarah/Library/Mobile Documents/com~apple~CloudDocs/Spring 2018/Operating Systems/hw2/cmake-build-debug/CMakeFiles/hw2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/hw2.dir/depend

