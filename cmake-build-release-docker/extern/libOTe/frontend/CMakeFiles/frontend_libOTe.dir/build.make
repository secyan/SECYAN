# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.mFVEfPI5GV

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker

# Include any dependencies generated for this target.
include extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/depend.make

# Include the progress variables for this target.
include extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/progress.make

# Include the compile flags for this target's objects.
include extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/flags.make

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/main.cpp.o: extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/flags.make
extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/main.cpp.o: ../extern/libOTe/frontend/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/main.cpp.o"
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/frontend_libOTe.dir/main.cpp.o -c /tmp/tmp.mFVEfPI5GV/extern/libOTe/frontend/main.cpp

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frontend_libOTe.dir/main.cpp.i"
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.mFVEfPI5GV/extern/libOTe/frontend/main.cpp > CMakeFiles/frontend_libOTe.dir/main.cpp.i

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frontend_libOTe.dir/main.cpp.s"
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.mFVEfPI5GV/extern/libOTe/frontend/main.cpp -o CMakeFiles/frontend_libOTe.dir/main.cpp.s

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/util.cpp.o: extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/flags.make
extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/util.cpp.o: ../extern/libOTe/frontend/util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/util.cpp.o"
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/frontend_libOTe.dir/util.cpp.o -c /tmp/tmp.mFVEfPI5GV/extern/libOTe/frontend/util.cpp

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frontend_libOTe.dir/util.cpp.i"
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.mFVEfPI5GV/extern/libOTe/frontend/util.cpp > CMakeFiles/frontend_libOTe.dir/util.cpp.i

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frontend_libOTe.dir/util.cpp.s"
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.mFVEfPI5GV/extern/libOTe/frontend/util.cpp -o CMakeFiles/frontend_libOTe.dir/util.cpp.s

# Object files for target frontend_libOTe
frontend_libOTe_OBJECTS = \
"CMakeFiles/frontend_libOTe.dir/main.cpp.o" \
"CMakeFiles/frontend_libOTe.dir/util.cpp.o"

# External object files for target frontend_libOTe
frontend_libOTe_EXTERNAL_OBJECTS =

extern/libOTe/frontend/frontend_libOTe: extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/main.cpp.o
extern/libOTe/frontend/frontend_libOTe: extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/util.cpp.o
extern/libOTe/frontend/frontend_libOTe: extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/build.make
extern/libOTe/frontend/frontend_libOTe: extern/libOTe/libOTe_Tests/liblibOTe_Tests.a
extern/libOTe/frontend/frontend_libOTe: extern/libOTe/cryptoTools/tests_cryptoTools/libtests_cryptoTools.a
extern/libOTe/frontend/frontend_libOTe: extern/libOTe/libOTe/liblibOTe.a
extern/libOTe/frontend/frontend_libOTe: extern/libOTe/cryptoTools/cryptoTools/libcryptoTools.a
extern/libOTe/frontend/frontend_libOTe: extern/ABY/lib/librelic_s.a
extern/libOTe/frontend/frontend_libOTe: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
extern/libOTe/frontend/frontend_libOTe: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
extern/libOTe/frontend/frontend_libOTe: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
extern/libOTe/frontend/frontend_libOTe: extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable frontend_libOTe"
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/frontend_libOTe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/build: extern/libOTe/frontend/frontend_libOTe

.PHONY : extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/build

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/clean:
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend && $(CMAKE_COMMAND) -P CMakeFiles/frontend_libOTe.dir/cmake_clean.cmake
.PHONY : extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/clean

extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/depend:
	cd /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.mFVEfPI5GV /tmp/tmp.mFVEfPI5GV/extern/libOTe/frontend /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend /tmp/tmp.mFVEfPI5GV/cmake-build-release-docker/extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extern/libOTe/frontend/CMakeFiles/frontend_libOTe.dir/depend

