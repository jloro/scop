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
include tests/CMakeFiles/vulkan.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/vulkan.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/vulkan.dir/flags.make

tests/CMakeFiles/vulkan.dir/vulkan.c.o: tests/CMakeFiles/vulkan.dir/flags.make
tests/CMakeFiles/vulkan.dir/vulkan.c.o: ../tests/vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jloro/scop/lib/glfw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/vulkan.dir/vulkan.c.o"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vulkan.dir/vulkan.c.o   -c /Users/jloro/scop/lib/glfw/tests/vulkan.c

tests/CMakeFiles/vulkan.dir/vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vulkan.dir/vulkan.c.i"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jloro/scop/lib/glfw/tests/vulkan.c > CMakeFiles/vulkan.dir/vulkan.c.i

tests/CMakeFiles/vulkan.dir/vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vulkan.dir/vulkan.c.s"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jloro/scop/lib/glfw/tests/vulkan.c -o CMakeFiles/vulkan.dir/vulkan.c.s

tests/CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.o: tests/CMakeFiles/vulkan.dir/flags.make
tests/CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.o: ../deps/glad_vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jloro/scop/lib/glfw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.o"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.o   -c /Users/jloro/scop/lib/glfw/deps/glad_vulkan.c

tests/CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.i"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jloro/scop/lib/glfw/deps/glad_vulkan.c > CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.i

tests/CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.s"
	cd /Users/jloro/scop/lib/glfw/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jloro/scop/lib/glfw/deps/glad_vulkan.c -o CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.s

# Object files for target vulkan
vulkan_OBJECTS = \
"CMakeFiles/vulkan.dir/vulkan.c.o" \
"CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.o"

# External object files for target vulkan
vulkan_EXTERNAL_OBJECTS =

tests/vulkan: tests/CMakeFiles/vulkan.dir/vulkan.c.o
tests/vulkan: tests/CMakeFiles/vulkan.dir/__/deps/glad_vulkan.c.o
tests/vulkan: tests/CMakeFiles/vulkan.dir/build.make
tests/vulkan: src/libglfw3.a
tests/vulkan: tests/CMakeFiles/vulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jloro/scop/lib/glfw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable vulkan"
	cd /Users/jloro/scop/lib/glfw/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/vulkan.dir/build: tests/vulkan

.PHONY : tests/CMakeFiles/vulkan.dir/build

tests/CMakeFiles/vulkan.dir/clean:
	cd /Users/jloro/scop/lib/glfw/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/vulkan.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/vulkan.dir/clean

tests/CMakeFiles/vulkan.dir/depend:
	cd /Users/jloro/scop/lib/glfw/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jloro/scop/lib/glfw /Users/jloro/scop/lib/glfw/tests /Users/jloro/scop/lib/glfw/build /Users/jloro/scop/lib/glfw/build/tests /Users/jloro/scop/lib/glfw/build/tests/CMakeFiles/vulkan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/vulkan.dir/depend
