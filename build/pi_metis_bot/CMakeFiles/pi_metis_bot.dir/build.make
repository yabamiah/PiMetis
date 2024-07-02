# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yaba/Sandbox/PiMetis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yaba/Sandbox/PiMetis/build

# Include any dependencies generated for this target.
include pi_metis_bot/CMakeFiles/pi_metis_bot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include pi_metis_bot/CMakeFiles/pi_metis_bot.dir/compiler_depend.make

# Include the progress variables for this target.
include pi_metis_bot/CMakeFiles/pi_metis_bot.dir/progress.make

# Include the compile flags for this target's objects.
include pi_metis_bot/CMakeFiles/pi_metis_bot.dir/flags.make

pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o: pi_metis_bot/CMakeFiles/pi_metis_bot.dir/flags.make
pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o: ../pi_metis_bot/pi_metis_bot.cpp
pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o: pi_metis_bot/CMakeFiles/pi_metis_bot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yaba/Sandbox/PiMetis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o"
	cd /home/yaba/Sandbox/PiMetis/build/pi_metis_bot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o -MF CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o.d -o CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o -c /home/yaba/Sandbox/PiMetis/pi_metis_bot/pi_metis_bot.cpp

pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.i"
	cd /home/yaba/Sandbox/PiMetis/build/pi_metis_bot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yaba/Sandbox/PiMetis/pi_metis_bot/pi_metis_bot.cpp > CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.i

pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.s"
	cd /home/yaba/Sandbox/PiMetis/build/pi_metis_bot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yaba/Sandbox/PiMetis/pi_metis_bot/pi_metis_bot.cpp -o CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.s

# Object files for target pi_metis_bot
pi_metis_bot_OBJECTS = \
"CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o"

# External object files for target pi_metis_bot
pi_metis_bot_EXTERNAL_OBJECTS =

pi_metis_bot/libpi_metis_bot.so: pi_metis_bot/CMakeFiles/pi_metis_bot.dir/pi_metis_bot.cpp.o
pi_metis_bot/libpi_metis_bot.so: pi_metis_bot/CMakeFiles/pi_metis_bot.dir/build.make
pi_metis_bot/libpi_metis_bot.so: _deps/cpr-build/cpr/libcpr.so.1.9.0
pi_metis_bot/libpi_metis_bot.so: _deps/curl-build/lib/libcurl.so
pi_metis_bot/libpi_metis_bot.so: /usr/lib/x86_64-linux-gnu/libssl.so
pi_metis_bot/libpi_metis_bot.so: /usr/lib/x86_64-linux-gnu/libcrypto.so
pi_metis_bot/libpi_metis_bot.so: /usr/local/lib/libz.so
pi_metis_bot/libpi_metis_bot.so: pi_metis_bot/CMakeFiles/pi_metis_bot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yaba/Sandbox/PiMetis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libpi_metis_bot.so"
	cd /home/yaba/Sandbox/PiMetis/build/pi_metis_bot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pi_metis_bot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pi_metis_bot/CMakeFiles/pi_metis_bot.dir/build: pi_metis_bot/libpi_metis_bot.so
.PHONY : pi_metis_bot/CMakeFiles/pi_metis_bot.dir/build

pi_metis_bot/CMakeFiles/pi_metis_bot.dir/clean:
	cd /home/yaba/Sandbox/PiMetis/build/pi_metis_bot && $(CMAKE_COMMAND) -P CMakeFiles/pi_metis_bot.dir/cmake_clean.cmake
.PHONY : pi_metis_bot/CMakeFiles/pi_metis_bot.dir/clean

pi_metis_bot/CMakeFiles/pi_metis_bot.dir/depend:
	cd /home/yaba/Sandbox/PiMetis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yaba/Sandbox/PiMetis /home/yaba/Sandbox/PiMetis/pi_metis_bot /home/yaba/Sandbox/PiMetis/build /home/yaba/Sandbox/PiMetis/build/pi_metis_bot /home/yaba/Sandbox/PiMetis/build/pi_metis_bot/CMakeFiles/pi_metis_bot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pi_metis_bot/CMakeFiles/pi_metis_bot.dir/depend

