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
CMAKE_SOURCE_DIR = "/Users/mac/Desktop/ClionProjects/Leader Price"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/mac/Desktop/ClionProjects/Leader Price/cmake-build-debug"

# Utility rule file for Leader_Price_autogen.

# Include the progress variables for this target.
include CMakeFiles/Leader_Price_autogen.dir/progress.make

CMakeFiles/Leader_Price_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/Users/mac/Desktop/ClionProjects/Leader Price/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC, UIC and RCC for target Leader_Price"
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -E cmake_autogen "/Users/mac/Desktop/ClionProjects/Leader Price/cmake-build-debug/CMakeFiles/Leader_Price_autogen.dir" Debug

Leader_Price_autogen: CMakeFiles/Leader_Price_autogen
Leader_Price_autogen: CMakeFiles/Leader_Price_autogen.dir/build.make

.PHONY : Leader_Price_autogen

# Rule to build all files generated by this target.
CMakeFiles/Leader_Price_autogen.dir/build: Leader_Price_autogen

.PHONY : CMakeFiles/Leader_Price_autogen.dir/build

CMakeFiles/Leader_Price_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Leader_Price_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Leader_Price_autogen.dir/clean

CMakeFiles/Leader_Price_autogen.dir/depend:
	cd "/Users/mac/Desktop/ClionProjects/Leader Price/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/mac/Desktop/ClionProjects/Leader Price" "/Users/mac/Desktop/ClionProjects/Leader Price" "/Users/mac/Desktop/ClionProjects/Leader Price/cmake-build-debug" "/Users/mac/Desktop/ClionProjects/Leader Price/cmake-build-debug" "/Users/mac/Desktop/ClionProjects/Leader Price/cmake-build-debug/CMakeFiles/Leader_Price_autogen.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Leader_Price_autogen.dir/depend

