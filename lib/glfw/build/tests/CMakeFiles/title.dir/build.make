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
CMAKE_COMMAND = /Users/jloro/.brew/Cellar/cmake/3.14.1/bin/cmake

# The command to remove a file.
RM = /Users/jloro/.brew/Cellar/cmake/3.14.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jloro/scop/lib/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jloro/scop/lib/glfw/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/title.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/title.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/title.dir/flags.make

tests/CMakeFiles/title.dir/title.c.o: tests/CMakeFiles/title.dir/flags.make
tests/CMakeFiles/title.dir/title.c.o: ../tests/title.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jloro/scop/lib/glfw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/title.dir/title.c.o"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/title.dir/title.c.o   -c /Users/jloro/scop/lib/glfw/tests/title.c

tests/CMakeFiles/title.dir/title.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/title.dir/title.c.i"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jloro/scop/lib/glfw/tests/title.c > CMakeFiles/title.dir/title.c.i

tests/CMakeFiles/title.dir/title.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/title.dir/title.c.s"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jloro/scop/lib/glfw/tests/title.c -o CMakeFiles/title.dir/title.c.s

tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/title.dir/flags.make
tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o: ../deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jloro/scop/lib/glfw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/title.dir/__/deps/glad_gl.c.o   -c /Users/jloro/scop/lib/glfw/deps/glad_gl.c

tests/CMakeFiles/title.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/title.dir/__/deps/glad_gl.c.i"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jloro/scop/lib/glfw/deps/glad_gl.c > CMakeFiles/title.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/title.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/title.dir/__/deps/glad_gl.c.s"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jloro/scop/lib/glfw/deps/glad_gl.c -o CMakeFiles/title.dir/__/deps/glad_gl.c.s

# Object files for target title
title_OBJECTS = \
"CMakeFiles/title.dir/title.c.o" \
"CMakeFiles/title.dir/__/deps/glad_gl.c.o"

# External object files for target title
title_EXTERNAL_OBJECTS =

tests/title.app/Contents/MacOS/title: tests/CMakeFiles/title.dir/title.c.o
tests/title.app/Contents/MacOS/title: tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o
tests/title.app/Contents/MacOS/title: tests/CMakeFiles/title.dir/build.make
tests/title.app/Contents/MacOS/title: src/libglfw3.a
tests/title.app/Contents/MacOS/title: tests/CMakeFiles/title.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jloro/scop/lib/glfw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable title.app/Contents/MacOS/title"
	cd /Users/jloro/scop/lib/glfw/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/title.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/title.dir/build: tests/title.app/Contents/MacOS/title

.PHONY : tests/CMakeFiles/title.dir/build

tests/CMakeFiles/title.dir/clean:
	cd /Users/jloro/scop/lib/glfw/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/title.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/title.dir/clean

tests/CMakeFiles/title.dir/depend:
	cd /Users/jloro/scop/lib/glfw/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jloro/scop/lib/glfw /Users/jloro/scop/lib/glfw/tests /Users/jloro/scop/lib/glfw/build /Users/jloro/scop/lib/glfw/build/tests /Users/jloro/scop/lib/glfw/build/tests/CMakeFiles/title.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/title.dir/depend

