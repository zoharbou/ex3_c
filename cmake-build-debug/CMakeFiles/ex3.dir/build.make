# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Bouchnik\Desktop\ex3\ex3_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex3.dir/flags.make

CMakeFiles/ex3.dir/calculator.c.obj: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/calculator.c.obj: ../calculator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ex3.dir/calculator.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ex3.dir\calculator.c.obj   -c C:\Users\Bouchnik\Desktop\ex3\ex3_c\calculator.c

CMakeFiles/ex3.dir/calculator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3.dir/calculator.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Bouchnik\Desktop\ex3\ex3_c\calculator.c > CMakeFiles\ex3.dir\calculator.c.i

CMakeFiles/ex3.dir/calculator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3.dir/calculator.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Bouchnik\Desktop\ex3\ex3_c\calculator.c -o CMakeFiles\ex3.dir\calculator.c.s

CMakeFiles/ex3.dir/reader.c.obj: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/reader.c.obj: ../reader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ex3.dir/reader.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ex3.dir\reader.c.obj   -c C:\Users\Bouchnik\Desktop\ex3\ex3_c\reader.c

CMakeFiles/ex3.dir/reader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3.dir/reader.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Bouchnik\Desktop\ex3\ex3_c\reader.c > CMakeFiles\ex3.dir\reader.c.i

CMakeFiles/ex3.dir/reader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3.dir/reader.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Bouchnik\Desktop\ex3\ex3_c\reader.c -o CMakeFiles\ex3.dir\reader.c.s

CMakeFiles/ex3.dir/heat_eqn.c.obj: CMakeFiles/ex3.dir/flags.make
CMakeFiles/ex3.dir/heat_eqn.c.obj: ../heat_eqn.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ex3.dir/heat_eqn.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ex3.dir\heat_eqn.c.obj   -c C:\Users\Bouchnik\Desktop\ex3\ex3_c\heat_eqn.c

CMakeFiles/ex3.dir/heat_eqn.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex3.dir/heat_eqn.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Bouchnik\Desktop\ex3\ex3_c\heat_eqn.c > CMakeFiles\ex3.dir\heat_eqn.c.i

CMakeFiles/ex3.dir/heat_eqn.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex3.dir/heat_eqn.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Bouchnik\Desktop\ex3\ex3_c\heat_eqn.c -o CMakeFiles\ex3.dir\heat_eqn.c.s

# Object files for target ex3
ex3_OBJECTS = \
"CMakeFiles/ex3.dir/calculator.c.obj" \
"CMakeFiles/ex3.dir/reader.c.obj" \
"CMakeFiles/ex3.dir/heat_eqn.c.obj"

# External object files for target ex3
ex3_EXTERNAL_OBJECTS =

ex3.exe: CMakeFiles/ex3.dir/calculator.c.obj
ex3.exe: CMakeFiles/ex3.dir/reader.c.obj
ex3.exe: CMakeFiles/ex3.dir/heat_eqn.c.obj
ex3.exe: CMakeFiles/ex3.dir/build.make
ex3.exe: CMakeFiles/ex3.dir/linklibs.rsp
ex3.exe: CMakeFiles/ex3.dir/objects1.rsp
ex3.exe: CMakeFiles/ex3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ex3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ex3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex3.dir/build: ex3.exe

.PHONY : CMakeFiles/ex3.dir/build

CMakeFiles/ex3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ex3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ex3.dir/clean

CMakeFiles/ex3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Bouchnik\Desktop\ex3\ex3_c C:\Users\Bouchnik\Desktop\ex3\ex3_c C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug C:\Users\Bouchnik\Desktop\ex3\ex3_c\cmake-build-debug\CMakeFiles\ex3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex3.dir/depend

