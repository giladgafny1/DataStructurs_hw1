# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Gilad\CLionProjects\DataStructurs_hw1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Gilad\CLionProjects\DataStructurs_hw1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DataStructurs_hw1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DataStructurs_hw1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DataStructurs_hw1.dir/flags.make

CMakeFiles/DataStructurs_hw1.dir/main1.cpp.obj: CMakeFiles/DataStructurs_hw1.dir/flags.make
CMakeFiles/DataStructurs_hw1.dir/main1.cpp.obj: ../main1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gilad\CLionProjects\DataStructurs_hw1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DataStructurs_hw1.dir/main1.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\DataStructurs_hw1.dir\main1.cpp.obj -c C:\Users\Gilad\CLionProjects\DataStructurs_hw1\main1.cpp

CMakeFiles/DataStructurs_hw1.dir/main1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DataStructurs_hw1.dir/main1.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Gilad\CLionProjects\DataStructurs_hw1\main1.cpp > CMakeFiles\DataStructurs_hw1.dir\main1.cpp.i

CMakeFiles/DataStructurs_hw1.dir/main1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DataStructurs_hw1.dir/main1.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Gilad\CLionProjects\DataStructurs_hw1\main1.cpp -o CMakeFiles\DataStructurs_hw1.dir\main1.cpp.s

# Object files for target DataStructurs_hw1
DataStructurs_hw1_OBJECTS = \
"CMakeFiles/DataStructurs_hw1.dir/main1.cpp.obj"

# External object files for target DataStructurs_hw1
DataStructurs_hw1_EXTERNAL_OBJECTS =

DataStructurs_hw1.exe: CMakeFiles/DataStructurs_hw1.dir/main1.cpp.obj
DataStructurs_hw1.exe: CMakeFiles/DataStructurs_hw1.dir/build.make
DataStructurs_hw1.exe: CMakeFiles/DataStructurs_hw1.dir/linklibs.rsp
DataStructurs_hw1.exe: CMakeFiles/DataStructurs_hw1.dir/objects1.rsp
DataStructurs_hw1.exe: CMakeFiles/DataStructurs_hw1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Gilad\CLionProjects\DataStructurs_hw1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DataStructurs_hw1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\DataStructurs_hw1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DataStructurs_hw1.dir/build: DataStructurs_hw1.exe

.PHONY : CMakeFiles/DataStructurs_hw1.dir/build

CMakeFiles/DataStructurs_hw1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DataStructurs_hw1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/DataStructurs_hw1.dir/clean

CMakeFiles/DataStructurs_hw1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Gilad\CLionProjects\DataStructurs_hw1 C:\Users\Gilad\CLionProjects\DataStructurs_hw1 C:\Users\Gilad\CLionProjects\DataStructurs_hw1\cmake-build-debug C:\Users\Gilad\CLionProjects\DataStructurs_hw1\cmake-build-debug C:\Users\Gilad\CLionProjects\DataStructurs_hw1\cmake-build-debug\CMakeFiles\DataStructurs_hw1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DataStructurs_hw1.dir/depend

