# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = "/c/Program Files (x86)/CMake 2.8/bin/cmake.exe"

# The command to remove a file.
RM = "/c/Program Files (x86)/CMake 2.8/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/c/Program Files (x86)/CMake 2.8/bin/cmake-gui.exe"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /D/SysData/Documents/GitHub/CmdOption

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /D/SysData/Documents/GitHub/CmdOption/build

# Include any dependencies generated for this target.
include src/CMakeFiles/cmdoption.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/cmdoption.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/cmdoption.dir/flags.make

src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj: src/CMakeFiles/cmdoption.dir/flags.make
src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj: src/CMakeFiles/cmdoption.dir/includes_CXX.rsp
src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj: ../src/CmdOptionList.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/SysData/Documents/GitHub/CmdOption/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj"
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj -c /D/SysData/Documents/GitHub/CmdOption/src/CmdOptionList.cpp

src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmdoption.dir/CmdOptionList.cpp.i"
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/SysData/Documents/GitHub/CmdOption/src/CmdOptionList.cpp > CMakeFiles/cmdoption.dir/CmdOptionList.cpp.i

src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmdoption.dir/CmdOptionList.cpp.s"
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/SysData/Documents/GitHub/CmdOption/src/CmdOptionList.cpp -o CMakeFiles/cmdoption.dir/CmdOptionList.cpp.s

src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.requires:
.PHONY : src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.requires

src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.provides: src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.requires
	$(MAKE) -f src/CMakeFiles/cmdoption.dir/build.make src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.provides.build
.PHONY : src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.provides

src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.provides.build: src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj

src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj: src/CMakeFiles/cmdoption.dir/flags.make
src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj: src/CMakeFiles/cmdoption.dir/includes_CXX.rsp
src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj: ../src/CmdOptionValue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /D/SysData/Documents/GitHub/CmdOption/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj"
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && /C/MinGW/bin/g++.exe   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj -c /D/SysData/Documents/GitHub/CmdOption/src/CmdOptionValue.cpp

src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.i"
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -E /D/SysData/Documents/GitHub/CmdOption/src/CmdOptionValue.cpp > CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.i

src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.s"
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && /C/MinGW/bin/g++.exe  $(CXX_DEFINES) $(CXX_FLAGS) -S /D/SysData/Documents/GitHub/CmdOption/src/CmdOptionValue.cpp -o CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.s

src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.requires:
.PHONY : src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.requires

src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.provides: src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.requires
	$(MAKE) -f src/CMakeFiles/cmdoption.dir/build.make src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.provides.build
.PHONY : src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.provides

src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.provides.build: src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj

# Object files for target cmdoption
cmdoption_OBJECTS = \
"CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj" \
"CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj"

# External object files for target cmdoption
cmdoption_EXTERNAL_OBJECTS =

../lib/libcmdoption.a: src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj
../lib/libcmdoption.a: src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj
../lib/libcmdoption.a: src/CMakeFiles/cmdoption.dir/build.make
../lib/libcmdoption.a: src/CMakeFiles/cmdoption.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libcmdoption.a"
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && $(CMAKE_COMMAND) -P CMakeFiles/cmdoption.dir/cmake_clean_target.cmake
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmdoption.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/cmdoption.dir/build: ../lib/libcmdoption.a
.PHONY : src/CMakeFiles/cmdoption.dir/build

src/CMakeFiles/cmdoption.dir/requires: src/CMakeFiles/cmdoption.dir/CmdOptionList.cpp.obj.requires
src/CMakeFiles/cmdoption.dir/requires: src/CMakeFiles/cmdoption.dir/CmdOptionValue.cpp.obj.requires
.PHONY : src/CMakeFiles/cmdoption.dir/requires

src/CMakeFiles/cmdoption.dir/clean:
	cd /D/SysData/Documents/GitHub/CmdOption/build/src && $(CMAKE_COMMAND) -P CMakeFiles/cmdoption.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/cmdoption.dir/clean

src/CMakeFiles/cmdoption.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /D/SysData/Documents/GitHub/CmdOption /D/SysData/Documents/GitHub/CmdOption/src /D/SysData/Documents/GitHub/CmdOption/build /D/SysData/Documents/GitHub/CmdOption/build/src /D/SysData/Documents/GitHub/CmdOption/build/src/CMakeFiles/cmdoption.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/cmdoption.dir/depend
