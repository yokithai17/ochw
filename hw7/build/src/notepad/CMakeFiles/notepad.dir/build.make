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
CMAKE_SOURCE_DIR = C:\Users\cl\ochw\hw7

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\cl\ochw\hw7\build

# Include any dependencies generated for this target.
include src/notepad/CMakeFiles/notepad.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/notepad/CMakeFiles/notepad.dir/compiler_depend.make

# Include the progress variables for this target.
include src/notepad/CMakeFiles/notepad.dir/progress.make

# Include the compile flags for this target's objects.
include src/notepad/CMakeFiles/notepad.dir/flags.make

src/notepad/CMakeFiles/notepad.dir/notepad.cpp.obj: src/notepad/CMakeFiles/notepad.dir/flags.make
src/notepad/CMakeFiles/notepad.dir/notepad.cpp.obj: src/notepad/CMakeFiles/notepad.dir/includes_CXX.rsp
src/notepad/CMakeFiles/notepad.dir/notepad.cpp.obj: C:/Users/cl/ochw/hw7/src/notepad/notepad.cpp
src/notepad/CMakeFiles/notepad.dir/notepad.cpp.obj: src/notepad/CMakeFiles/notepad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\cl\ochw\hw7\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/notepad/CMakeFiles/notepad.dir/notepad.cpp.obj"
	cd /d C:\Users\cl\ochw\hw7\build\src\notepad && C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/notepad/CMakeFiles/notepad.dir/notepad.cpp.obj -MF CMakeFiles\notepad.dir\notepad.cpp.obj.d -o CMakeFiles\notepad.dir\notepad.cpp.obj -c C:\Users\cl\ochw\hw7\src\notepad\notepad.cpp

src/notepad/CMakeFiles/notepad.dir/notepad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/notepad.dir/notepad.cpp.i"
	cd /d C:\Users\cl\ochw\hw7\build\src\notepad && C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\cl\ochw\hw7\src\notepad\notepad.cpp > CMakeFiles\notepad.dir\notepad.cpp.i

src/notepad/CMakeFiles/notepad.dir/notepad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/notepad.dir/notepad.cpp.s"
	cd /d C:\Users\cl\ochw\hw7\build\src\notepad && C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\cl\ochw\hw7\src\notepad\notepad.cpp -o CMakeFiles\notepad.dir\notepad.cpp.s

# Object files for target notepad
notepad_OBJECTS = \
"CMakeFiles/notepad.dir/notepad.cpp.obj"

# External object files for target notepad
notepad_EXTERNAL_OBJECTS =

src/notepad/libnotepad.a: src/notepad/CMakeFiles/notepad.dir/notepad.cpp.obj
src/notepad/libnotepad.a: src/notepad/CMakeFiles/notepad.dir/build.make
src/notepad/libnotepad.a: src/notepad/CMakeFiles/notepad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\cl\ochw\hw7\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libnotepad.a"
	cd /d C:\Users\cl\ochw\hw7\build\src\notepad && $(CMAKE_COMMAND) -P CMakeFiles\notepad.dir\cmake_clean_target.cmake
	cd /d C:\Users\cl\ochw\hw7\build\src\notepad && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\notepad.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/notepad/CMakeFiles/notepad.dir/build: src/notepad/libnotepad.a
.PHONY : src/notepad/CMakeFiles/notepad.dir/build

src/notepad/CMakeFiles/notepad.dir/clean:
	cd /d C:\Users\cl\ochw\hw7\build\src\notepad && $(CMAKE_COMMAND) -P CMakeFiles\notepad.dir\cmake_clean.cmake
.PHONY : src/notepad/CMakeFiles/notepad.dir/clean

src/notepad/CMakeFiles/notepad.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\cl\ochw\hw7 C:\Users\cl\ochw\hw7\src\notepad C:\Users\cl\ochw\hw7\build C:\Users\cl\ochw\hw7\build\src\notepad C:\Users\cl\ochw\hw7\build\src\notepad\CMakeFiles\notepad.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/notepad/CMakeFiles/notepad.dir/depend

