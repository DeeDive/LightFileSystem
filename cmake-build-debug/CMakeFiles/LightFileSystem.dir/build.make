# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2019.1.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.1.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cloudii/Documents/LightFileSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cloudii/Documents/LightFileSystem/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LightFileSystem.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LightFileSystem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LightFileSystem.dir/flags.make

CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.o: CMakeFiles/LightFileSystem.dir/flags.make
CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.o: ../SuperBlock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cloudii/Documents/LightFileSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.o -c /home/cloudii/Documents/LightFileSystem/SuperBlock.cpp

CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cloudii/Documents/LightFileSystem/SuperBlock.cpp > CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.i

CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cloudii/Documents/LightFileSystem/SuperBlock.cpp -o CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.s

CMakeFiles/LightFileSystem.dir/iNode.cpp.o: CMakeFiles/LightFileSystem.dir/flags.make
CMakeFiles/LightFileSystem.dir/iNode.cpp.o: ../iNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cloudii/Documents/LightFileSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/LightFileSystem.dir/iNode.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LightFileSystem.dir/iNode.cpp.o -c /home/cloudii/Documents/LightFileSystem/iNode.cpp

CMakeFiles/LightFileSystem.dir/iNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LightFileSystem.dir/iNode.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cloudii/Documents/LightFileSystem/iNode.cpp > CMakeFiles/LightFileSystem.dir/iNode.cpp.i

CMakeFiles/LightFileSystem.dir/iNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LightFileSystem.dir/iNode.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cloudii/Documents/LightFileSystem/iNode.cpp -o CMakeFiles/LightFileSystem.dir/iNode.cpp.s

CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.o: CMakeFiles/LightFileSystem.dir/flags.make
CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.o: ../LightFileSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cloudii/Documents/LightFileSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.o -c /home/cloudii/Documents/LightFileSystem/LightFileSystem.cpp

CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cloudii/Documents/LightFileSystem/LightFileSystem.cpp > CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.i

CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cloudii/Documents/LightFileSystem/LightFileSystem.cpp -o CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.s

CMakeFiles/LightFileSystem.dir/dir.cpp.o: CMakeFiles/LightFileSystem.dir/flags.make
CMakeFiles/LightFileSystem.dir/dir.cpp.o: ../dir.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cloudii/Documents/LightFileSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/LightFileSystem.dir/dir.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LightFileSystem.dir/dir.cpp.o -c /home/cloudii/Documents/LightFileSystem/dir.cpp

CMakeFiles/LightFileSystem.dir/dir.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LightFileSystem.dir/dir.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cloudii/Documents/LightFileSystem/dir.cpp > CMakeFiles/LightFileSystem.dir/dir.cpp.i

CMakeFiles/LightFileSystem.dir/dir.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LightFileSystem.dir/dir.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cloudii/Documents/LightFileSystem/dir.cpp -o CMakeFiles/LightFileSystem.dir/dir.cpp.s

# Object files for target LightFileSystem
LightFileSystem_OBJECTS = \
"CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.o" \
"CMakeFiles/LightFileSystem.dir/iNode.cpp.o" \
"CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.o" \
"CMakeFiles/LightFileSystem.dir/dir.cpp.o"

# External object files for target LightFileSystem
LightFileSystem_EXTERNAL_OBJECTS =

LightFileSystem: CMakeFiles/LightFileSystem.dir/SuperBlock.cpp.o
LightFileSystem: CMakeFiles/LightFileSystem.dir/iNode.cpp.o
LightFileSystem: CMakeFiles/LightFileSystem.dir/LightFileSystem.cpp.o
LightFileSystem: CMakeFiles/LightFileSystem.dir/dir.cpp.o
LightFileSystem: CMakeFiles/LightFileSystem.dir/build.make
LightFileSystem: CMakeFiles/LightFileSystem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cloudii/Documents/LightFileSystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable LightFileSystem"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LightFileSystem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LightFileSystem.dir/build: LightFileSystem

.PHONY : CMakeFiles/LightFileSystem.dir/build

CMakeFiles/LightFileSystem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LightFileSystem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LightFileSystem.dir/clean

CMakeFiles/LightFileSystem.dir/depend:
	cd /home/cloudii/Documents/LightFileSystem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cloudii/Documents/LightFileSystem /home/cloudii/Documents/LightFileSystem /home/cloudii/Documents/LightFileSystem/cmake-build-debug /home/cloudii/Documents/LightFileSystem/cmake-build-debug /home/cloudii/Documents/LightFileSystem/cmake-build-debug/CMakeFiles/LightFileSystem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LightFileSystem.dir/depend

