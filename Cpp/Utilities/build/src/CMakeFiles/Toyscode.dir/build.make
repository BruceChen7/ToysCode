# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bruce/ToysCode/Cpp/Utilities

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bruce/ToysCode/Cpp/Utilities/build

# Include any dependencies generated for this target.
include src/CMakeFiles/Toyscode.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Toyscode.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Toyscode.dir/flags.make

src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o: src/CMakeFiles/Toyscode.dir/flags.make
src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o: ../src/get_first_follow.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bruce/ToysCode/Cpp/Utilities/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Toyscode.dir/get_first_follow.cc.o -c /home/bruce/ToysCode/Cpp/Utilities/src/get_first_follow.cc

src/CMakeFiles/Toyscode.dir/get_first_follow.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Toyscode.dir/get_first_follow.cc.i"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bruce/ToysCode/Cpp/Utilities/src/get_first_follow.cc > CMakeFiles/Toyscode.dir/get_first_follow.cc.i

src/CMakeFiles/Toyscode.dir/get_first_follow.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Toyscode.dir/get_first_follow.cc.s"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bruce/ToysCode/Cpp/Utilities/src/get_first_follow.cc -o CMakeFiles/Toyscode.dir/get_first_follow.cc.s

src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.requires:
.PHONY : src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.requires

src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.provides: src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.requires
	$(MAKE) -f src/CMakeFiles/Toyscode.dir/build.make src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.provides.build
.PHONY : src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.provides

src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.provides.build: src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o

src/CMakeFiles/Toyscode.dir/logging.cc.o: src/CMakeFiles/Toyscode.dir/flags.make
src/CMakeFiles/Toyscode.dir/logging.cc.o: ../src/logging.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bruce/ToysCode/Cpp/Utilities/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/Toyscode.dir/logging.cc.o"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Toyscode.dir/logging.cc.o -c /home/bruce/ToysCode/Cpp/Utilities/src/logging.cc

src/CMakeFiles/Toyscode.dir/logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Toyscode.dir/logging.cc.i"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bruce/ToysCode/Cpp/Utilities/src/logging.cc > CMakeFiles/Toyscode.dir/logging.cc.i

src/CMakeFiles/Toyscode.dir/logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Toyscode.dir/logging.cc.s"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bruce/ToysCode/Cpp/Utilities/src/logging.cc -o CMakeFiles/Toyscode.dir/logging.cc.s

src/CMakeFiles/Toyscode.dir/logging.cc.o.requires:
.PHONY : src/CMakeFiles/Toyscode.dir/logging.cc.o.requires

src/CMakeFiles/Toyscode.dir/logging.cc.o.provides: src/CMakeFiles/Toyscode.dir/logging.cc.o.requires
	$(MAKE) -f src/CMakeFiles/Toyscode.dir/build.make src/CMakeFiles/Toyscode.dir/logging.cc.o.provides.build
.PHONY : src/CMakeFiles/Toyscode.dir/logging.cc.o.provides

src/CMakeFiles/Toyscode.dir/logging.cc.o.provides.build: src/CMakeFiles/Toyscode.dir/logging.cc.o

src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o: src/CMakeFiles/Toyscode.dir/flags.make
src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o: ../src/re_to_nfa.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bruce/ToysCode/Cpp/Utilities/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Toyscode.dir/re_to_nfa.cc.o -c /home/bruce/ToysCode/Cpp/Utilities/src/re_to_nfa.cc

src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Toyscode.dir/re_to_nfa.cc.i"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bruce/ToysCode/Cpp/Utilities/src/re_to_nfa.cc > CMakeFiles/Toyscode.dir/re_to_nfa.cc.i

src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Toyscode.dir/re_to_nfa.cc.s"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bruce/ToysCode/Cpp/Utilities/src/re_to_nfa.cc -o CMakeFiles/Toyscode.dir/re_to_nfa.cc.s

src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.requires:
.PHONY : src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.requires

src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.provides: src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.requires
	$(MAKE) -f src/CMakeFiles/Toyscode.dir/build.make src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.provides.build
.PHONY : src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.provides

src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.provides.build: src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o

# Object files for target Toyscode
Toyscode_OBJECTS = \
"CMakeFiles/Toyscode.dir/get_first_follow.cc.o" \
"CMakeFiles/Toyscode.dir/logging.cc.o" \
"CMakeFiles/Toyscode.dir/re_to_nfa.cc.o"

# External object files for target Toyscode
Toyscode_EXTERNAL_OBJECTS =

src/libToyscode.a: src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o
src/libToyscode.a: src/CMakeFiles/Toyscode.dir/logging.cc.o
src/libToyscode.a: src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o
src/libToyscode.a: src/CMakeFiles/Toyscode.dir/build.make
src/libToyscode.a: src/CMakeFiles/Toyscode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libToyscode.a"
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Toyscode.dir/cmake_clean_target.cmake
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Toyscode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Toyscode.dir/build: src/libToyscode.a
.PHONY : src/CMakeFiles/Toyscode.dir/build

src/CMakeFiles/Toyscode.dir/requires: src/CMakeFiles/Toyscode.dir/get_first_follow.cc.o.requires
src/CMakeFiles/Toyscode.dir/requires: src/CMakeFiles/Toyscode.dir/logging.cc.o.requires
src/CMakeFiles/Toyscode.dir/requires: src/CMakeFiles/Toyscode.dir/re_to_nfa.cc.o.requires
.PHONY : src/CMakeFiles/Toyscode.dir/requires

src/CMakeFiles/Toyscode.dir/clean:
	cd /home/bruce/ToysCode/Cpp/Utilities/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Toyscode.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Toyscode.dir/clean

src/CMakeFiles/Toyscode.dir/depend:
	cd /home/bruce/ToysCode/Cpp/Utilities/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bruce/ToysCode/Cpp/Utilities /home/bruce/ToysCode/Cpp/Utilities/src /home/bruce/ToysCode/Cpp/Utilities/build /home/bruce/ToysCode/Cpp/Utilities/build/src /home/bruce/ToysCode/Cpp/Utilities/build/src/CMakeFiles/Toyscode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Toyscode.dir/depend

