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
include src/CMakeFiles/nlib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/nlib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/nlib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/nlib.dir/flags.make

src/CMakeFiles/nlib.dir/notepad.cpp.obj: src/CMakeFiles/nlib.dir/flags.make
src/CMakeFiles/nlib.dir/notepad.cpp.obj: src/CMakeFiles/nlib.dir/includes_CXX.rsp
src/CMakeFiles/nlib.dir/notepad.cpp.obj: C:/Users/cl/ochw/hw4/src/notepad.cpp
src/CMakeFiles/nlib.dir/notepad.cpp.obj: src/CMakeFiles/nlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\cl\ochw\hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/nlib.dir/notepad.cpp.obj"
	cd /d C:\Users\cl\ochw\hw4\build\src && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/nlib.dir/notepad.cpp.obj -MF CMakeFiles\nlib.dir\notepad.cpp.obj.d -o CMakeFiles\nlib.dir\notepad.cpp.obj -c C:\Users\cl\ochw\hw4\src\notepad.cpp

src/CMakeFiles/nlib.dir/notepad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nlib.dir/notepad.cpp.i"
	cd /d C:\Users\cl\ochw\hw4\build\src && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\cl\ochw\hw4\src\notepad.cpp > CMakeFiles\nlib.dir\notepad.cpp.i

src/CMakeFiles/nlib.dir/notepad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nlib.dir/notepad.cpp.s"
	cd /d C:\Users\cl\ochw\hw4\build\src && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\cl\ochw\hw4\src\notepad.cpp -o CMakeFiles\nlib.dir\notepad.cpp.s

src/CMakeFiles/nlib.dir/__/saver.cpp.obj: src/CMakeFiles/nlib.dir/flags.make
src/CMakeFiles/nlib.dir/__/saver.cpp.obj: src/CMakeFiles/nlib.dir/includes_CXX.rsp
src/CMakeFiles/nlib.dir/__/saver.cpp.obj: C:/Users/cl/ochw/hw4/saver.cpp
src/CMakeFiles/nlib.dir/__/saver.cpp.obj: src/CMakeFiles/nlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\cl\ochw\hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/nlib.dir/__/saver.cpp.obj"
	cd /d C:\Users\cl\ochw\hw4\build\src && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/nlib.dir/__/saver.cpp.obj -MF CMakeFiles\nlib.dir\__\saver.cpp.obj.d -o CMakeFiles\nlib.dir\__\saver.cpp.obj -c C:\Users\cl\ochw\hw4\saver.cpp

src/CMakeFiles/nlib.dir/__/saver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/nlib.dir/__/saver.cpp.i"
	cd /d C:\Users\cl\ochw\hw4\build\src && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\cl\ochw\hw4\saver.cpp > CMakeFiles\nlib.dir\__\saver.cpp.i

src/CMakeFiles/nlib.dir/__/saver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/nlib.dir/__/saver.cpp.s"
	cd /d C:\Users\cl\ochw\hw4\build\src && "E:\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\cl\ochw\hw4\saver.cpp -o CMakeFiles\nlib.dir\__\saver.cpp.s

# Object files for target nlib
nlib_OBJECTS = \
"CMakeFiles/nlib.dir/notepad.cpp.obj" \
"CMakeFiles/nlib.dir/__/saver.cpp.obj"

# External object files for target nlib
nlib_EXTERNAL_OBJECTS =

C:/Users/cl/ochw/hw4/bin/libnlib.dll: src/CMakeFiles/nlib.dir/notepad.cpp.obj
C:/Users/cl/ochw/hw4/bin/libnlib.dll: src/CMakeFiles/nlib.dir/__/saver.cpp.obj
C:/Users/cl/ochw/hw4/bin/libnlib.dll: src/CMakeFiles/nlib.dir/build.make
C:/Users/cl/ochw/hw4/bin/libnlib.dll: src/CMakeFiles/nlib.dir/linkLibs.rsp
C:/Users/cl/ochw/hw4/bin/libnlib.dll: src/CMakeFiles/nlib.dir/objects1.rsp
C:/Users/cl/ochw/hw4/bin/libnlib.dll: src/CMakeFiles/nlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\cl\ochw\hw4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library C:\Users\cl\ochw\hw4\bin\libnlib.dll"
	cd /d C:\Users\cl\ochw\hw4\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\nlib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/nlib.dir/build: C:/Users/cl/ochw/hw4/bin/libnlib.dll
.PHONY : src/CMakeFiles/nlib.dir/build

src/CMakeFiles/nlib.dir/clean:
	cd /d C:\Users\cl\ochw\hw4\build\src && $(CMAKE_COMMAND) -P CMakeFiles\nlib.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/nlib.dir/clean

src/CMakeFiles/nlib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\cl\ochw\hw4 C:\Users\cl\ochw\hw4\src C:\Users\cl\ochw\hw4\build C:\Users\cl\ochw\hw4\build\src C:\Users\cl\ochw\hw4\build\src\CMakeFiles\nlib.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/nlib.dir/depend

