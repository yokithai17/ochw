# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = "E:\CLion 2024.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "E:\CLion 2024.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\cl\ochw\hw4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\cl\ochw\hw4\build

# Include any dependencies generated for this target.
include src/saver/CMakeFiles/saver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/saver/CMakeFiles/saver.dir/compiler_depend.make

# Include the progress variables for this target.
include src/saver/CMakeFiles/saver.dir/progress.make

# Include the compile flags for this target's objects.
include src/saver/CMakeFiles/saver.dir/flags.make

src/saver/CMakeFiles/saver.dir/saver.cpp.obj: src/saver/CMakeFiles/saver.dir/flags.make
src/saver/CMakeFiles/saver.dir/saver.cpp.obj: src/saver/CMakeFiles/saver.dir/includes_CXX.rsp
src/saver/CMakeFiles/saver.dir/saver.cpp.obj: C:/Users/cl/ochw/hw4/src/saver/saver.cpp
src/saver/CMakeFiles/saver.dir/saver.cpp.obj: src/saver/CMakeFiles/saver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\cl\ochw\hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/saver/CMakeFiles/saver.dir/saver.cpp.obj"
	cd /d C:\Users\cl\ochw\hw4\build\src\saver && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/saver/CMakeFiles/saver.dir/saver.cpp.obj -MF CMakeFiles\saver.dir\saver.cpp.obj.d -o CMakeFiles\saver.dir\saver.cpp.obj -c C:\Users\cl\ochw\hw4\src\saver\saver.cpp

src/saver/CMakeFiles/saver.dir/saver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/saver.dir/saver.cpp.i"
	cd /d C:\Users\cl\ochw\hw4\build\src\saver && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\cl\ochw\hw4\src\saver\saver.cpp > CMakeFiles\saver.dir\saver.cpp.i

src/saver/CMakeFiles/saver.dir/saver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/saver.dir/saver.cpp.s"
	cd /d C:\Users\cl\ochw\hw4\build\src\saver && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\cl\ochw\hw4\src\saver\saver.cpp -o CMakeFiles\saver.dir\saver.cpp.s

# Object files for target saver
saver_OBJECTS = \
"CMakeFiles/saver.dir/saver.cpp.obj"

# External object files for target saver
saver_EXTERNAL_OBJECTS =

C:/Users/cl/ochw/hw4/bin/libsaver.dll: src/saver/CMakeFiles/saver.dir/saver.cpp.obj
C:/Users/cl/ochw/hw4/bin/libsaver.dll: src/saver/CMakeFiles/saver.dir/build.make
C:/Users/cl/ochw/hw4/bin/libsaver.dll: src/saver/CMakeFiles/saver.dir/linkLibs.rsp
C:/Users/cl/ochw/hw4/bin/libsaver.dll: src/saver/CMakeFiles/saver.dir/objects1.rsp
C:/Users/cl/ochw/hw4/bin/libsaver.dll: src/saver/CMakeFiles/saver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\cl\ochw\hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library C:\Users\cl\ochw\hw4\bin\libsaver.dll"
	cd /d C:\Users\cl\ochw\hw4\build\src\saver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\saver.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/saver/CMakeFiles/saver.dir/build: C:/Users/cl/ochw/hw4/bin/libsaver.dll
.PHONY : src/saver/CMakeFiles/saver.dir/build

src/saver/CMakeFiles/saver.dir/clean:
	cd /d C:\Users\cl\ochw\hw4\build\src\saver && $(CMAKE_COMMAND) -P CMakeFiles\saver.dir\cmake_clean.cmake
.PHONY : src/saver/CMakeFiles/saver.dir/clean

src/saver/CMakeFiles/saver.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\cl\ochw\hw4 C:\Users\cl\ochw\hw4\src\saver C:\Users\cl\ochw\hw4\build C:\Users\cl\ochw\hw4\build\src\saver C:\Users\cl\ochw\hw4\build\src\saver\CMakeFiles\saver.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/saver/CMakeFiles/saver.dir/depend

