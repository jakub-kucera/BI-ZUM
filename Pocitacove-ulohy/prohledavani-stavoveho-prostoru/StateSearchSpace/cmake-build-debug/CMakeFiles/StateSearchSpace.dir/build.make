# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/kucerj56/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kucerj56/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/StateSearchSpace.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StateSearchSpace.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StateSearchSpace.dir/flags.make

CMakeFiles/StateSearchSpace.dir/src/main.cpp.o: CMakeFiles/StateSearchSpace.dir/flags.make
CMakeFiles/StateSearchSpace.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StateSearchSpace.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StateSearchSpace.dir/src/main.cpp.o -c /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/src/main.cpp

CMakeFiles/StateSearchSpace.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StateSearchSpace.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/src/main.cpp > CMakeFiles/StateSearchSpace.dir/src/main.cpp.i

CMakeFiles/StateSearchSpace.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StateSearchSpace.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/src/main.cpp -o CMakeFiles/StateSearchSpace.dir/src/main.cpp.s

CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.o: CMakeFiles/StateSearchSpace.dir/flags.make
CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.o: ../src/CApplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.o -c /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/src/CApplication.cpp

CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/src/CApplication.cpp > CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.i

CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/src/CApplication.cpp -o CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.s

# Object files for target StateSearchSpace
StateSearchSpace_OBJECTS = \
"CMakeFiles/StateSearchSpace.dir/src/main.cpp.o" \
"CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.o"

# External object files for target StateSearchSpace
StateSearchSpace_EXTERNAL_OBJECTS =

StateSearchSpace: CMakeFiles/StateSearchSpace.dir/src/main.cpp.o
StateSearchSpace: CMakeFiles/StateSearchSpace.dir/src/CApplication.cpp.o
StateSearchSpace: CMakeFiles/StateSearchSpace.dir/build.make
StateSearchSpace: CMakeFiles/StateSearchSpace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable StateSearchSpace"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StateSearchSpace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StateSearchSpace.dir/build: StateSearchSpace

.PHONY : CMakeFiles/StateSearchSpace.dir/build

CMakeFiles/StateSearchSpace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StateSearchSpace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StateSearchSpace.dir/clean

CMakeFiles/StateSearchSpace.dir/depend:
	cd /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug /home/kucerj56/Documents/ZUM/bi-zum-ls2021-kucerj56/Pocitacove-ulohy/prohledavani-stavoveho-prostoru/StateSearchSpace/cmake-build-debug/CMakeFiles/StateSearchSpace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StateSearchSpace.dir/depend

