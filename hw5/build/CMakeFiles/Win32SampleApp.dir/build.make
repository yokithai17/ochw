# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\cl\ochw\hw5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\cl\ochw\hw5\build

# Include any dependencies generated for this target.
include CMakeFiles/Win32SampleApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Win32SampleApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Win32SampleApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Win32SampleApp.dir/flags.make

CMakeFiles/Win32SampleApp.dir/main.cpp.obj: CMakeFiles/Win32SampleApp.dir/flags.make
CMakeFiles/Win32SampleApp.dir/main.cpp.obj: CMakeFiles/Win32SampleApp.dir/includes_CXX.rsp
CMakeFiles/Win32SampleApp.dir/main.cpp.obj: C:/Users/cl/ochw/hw5/main.cpp
CMakeFiles/Win32SampleApp.dir/main.cpp.obj: CMakeFiles/Win32SampleApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\cl\ochw\hw5\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Win32SampleApp.dir/main.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Win32SampleApp.dir/main.cpp.obj -MF CMakeFiles\Win32SampleApp.dir\main.cpp.obj.d -o CMakeFiles\Win32SampleApp.dir\main.cpp.obj -c C:\Users\cl\ochw\hw5\main.cpp

CMakeFiles/Win32SampleApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Win32SampleApp.dir/main.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\cl\ochw\hw5\main.cpp > CMakeFiles\Win32SampleApp.dir\main.cpp.i

CMakeFiles/Win32SampleApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Win32SampleApp.dir/main.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\cl\ochw\hw5\main.cpp -o CMakeFiles\Win32SampleApp.dir\main.cpp.s

# Object files for target Win32SampleApp
Win32SampleApp_OBJECTS = \
"CMakeFiles/Win32SampleApp.dir/main.cpp.obj"

# External object files for target Win32SampleApp
Win32SampleApp_EXTERNAL_OBJECTS =

C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: CMakeFiles/Win32SampleApp.dir/main.cpp.obj
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: CMakeFiles/Win32SampleApp.dir/build.make
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: src/notepad/libnotepad.dll.a
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: src/saver/libsaver.dll.a
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: src/loader/libloader.dll.a
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: src/Config/libconfig.dll.a
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: CMakeFiles/Win32SampleApp.dir/linkLibs.rsp
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: CMakeFiles/Win32SampleApp.dir/objects1.rsp
C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe: CMakeFiles/Win32SampleApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\cl\ochw\hw5\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C:\Users\cl\ochw\hw5\bin\Win32SampleApp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Win32SampleApp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Win32SampleApp.dir/build: C:/Users/cl/ochw/hw5/bin/Win32SampleApp.exe
.PHONY : CMakeFiles/Win32SampleApp.dir/build

CMakeFiles/Win32SampleApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Win32SampleApp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Win32SampleApp.dir/clean

CMakeFiles/Win32SampleApp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\cl\ochw\hw5 C:\Users\cl\ochw\hw5 C:\Users\cl\ochw\hw5\build C:\Users\cl\ochw\hw5\build C:\Users\cl\ochw\hw5\build\CMakeFiles\Win32SampleApp.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Win32SampleApp.dir/depend
