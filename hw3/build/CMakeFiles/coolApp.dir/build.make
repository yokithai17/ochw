# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = C:/CMake/bin/cmake.exe

# The command to remove a file.
RM = C:/CMake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/olofk/oc_kal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/olofk/oc_kal/build

# Include any dependencies generated for this target.
include CMakeFiles/coolApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/coolApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/coolApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/coolApp.dir/flags.make

CMakeFiles/coolApp.dir/main.cpp.obj: CMakeFiles/coolApp.dir/flags.make
CMakeFiles/coolApp.dir/main.cpp.obj: C:/Users/olofk/oc_kal/main.cpp
CMakeFiles/coolApp.dir/main.cpp.obj: CMakeFiles/coolApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/Users/olofk/oc_kal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/coolApp.dir/main.cpp.obj"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/coolApp.dir/main.cpp.obj -MF CMakeFiles/coolApp.dir/main.cpp.obj.d -o CMakeFiles/coolApp.dir/main.cpp.obj -c C:/Users/olofk/oc_kal/main.cpp

CMakeFiles/coolApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/coolApp.dir/main.cpp.i"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/olofk/oc_kal/main.cpp > CMakeFiles/coolApp.dir/main.cpp.i

CMakeFiles/coolApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/coolApp.dir/main.cpp.s"
	C:/MinGW/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/olofk/oc_kal/main.cpp -o CMakeFiles/coolApp.dir/main.cpp.s

# Object files for target coolApp
coolApp_OBJECTS = \
"CMakeFiles/coolApp.dir/main.cpp.obj"

# External object files for target coolApp
coolApp_EXTERNAL_OBJECTS =

C:/Users/olofk/oc_kal/bin/coolApp.exe: CMakeFiles/coolApp.dir/main.cpp.obj
C:/Users/olofk/oc_kal/bin/coolApp.exe: CMakeFiles/coolApp.dir/build.make
C:/Users/olofk/oc_kal/bin/coolApp.exe: CMakeFiles/coolApp.dir/linkLibs.rsp
C:/Users/olofk/oc_kal/bin/coolApp.exe: CMakeFiles/coolApp.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:/Users/olofk/oc_kal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C:/Users/olofk/oc_kal/bin/coolApp.exe"
	C:/CMake/bin/cmake.exe -E rm -f CMakeFiles/coolApp.dir/objects.a
	C:/MinGW/bin/ar.exe qc CMakeFiles/coolApp.dir/objects.a @CMakeFiles/coolApp.dir/objects1.rsp
	C:/MinGW/bin/c++.exe -mwindows -Wl,--whole-archive CMakeFiles/coolApp.dir/objects.a -Wl,--no-whole-archive -o C:/Users/olofk/oc_kal/bin/coolApp.exe -Wl,--out-implib,libcoolApp.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/coolApp.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/coolApp.dir/build: C:/Users/olofk/oc_kal/bin/coolApp.exe
.PHONY : CMakeFiles/coolApp.dir/build

CMakeFiles/coolApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/coolApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/coolApp.dir/clean

CMakeFiles/coolApp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/olofk/oc_kal C:/Users/olofk/oc_kal C:/Users/olofk/oc_kal/build C:/Users/olofk/oc_kal/build C:/Users/olofk/oc_kal/build/CMakeFiles/coolApp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/coolApp.dir/depend

