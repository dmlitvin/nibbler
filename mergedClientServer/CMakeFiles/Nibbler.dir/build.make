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
CMAKE_COMMAND = /Users/kpshenyc/.brew/Cellar/cmake/3.14.5/bin/cmake

# The command to remove a file.
RM = /Users/kpshenyc/.brew/Cellar/cmake/3.14.5/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kpshenyc/nibbler/mergedClientServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kpshenyc/nibbler/mergedClientServer

# Include any dependencies generated for this target.
include CMakeFiles/Nibbler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Nibbler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Nibbler.dir/flags.make

CMakeFiles/Nibbler.dir/Server.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/Server.cpp.o: Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Nibbler.dir/Server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/Server.cpp.o -c /Users/kpshenyc/nibbler/mergedClientServer/Server.cpp

CMakeFiles/Nibbler.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/Server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kpshenyc/nibbler/mergedClientServer/Server.cpp > CMakeFiles/Nibbler.dir/Server.cpp.i

CMakeFiles/Nibbler.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/Server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kpshenyc/nibbler/mergedClientServer/Server.cpp -o CMakeFiles/Nibbler.dir/Server.cpp.s

CMakeFiles/Nibbler.dir/ClientController.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/ClientController.cpp.o: ClientController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Nibbler.dir/ClientController.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/ClientController.cpp.o -c /Users/kpshenyc/nibbler/mergedClientServer/ClientController.cpp

CMakeFiles/Nibbler.dir/ClientController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/ClientController.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kpshenyc/nibbler/mergedClientServer/ClientController.cpp > CMakeFiles/Nibbler.dir/ClientController.cpp.i

CMakeFiles/Nibbler.dir/ClientController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/ClientController.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kpshenyc/nibbler/mergedClientServer/ClientController.cpp -o CMakeFiles/Nibbler.dir/ClientController.cpp.s

CMakeFiles/Nibbler.dir/Snake.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/Snake.cpp.o: Snake.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Nibbler.dir/Snake.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/Snake.cpp.o -c /Users/kpshenyc/nibbler/mergedClientServer/Snake.cpp

CMakeFiles/Nibbler.dir/Snake.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/Snake.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kpshenyc/nibbler/mergedClientServer/Snake.cpp > CMakeFiles/Nibbler.dir/Snake.cpp.i

CMakeFiles/Nibbler.dir/Snake.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/Snake.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kpshenyc/nibbler/mergedClientServer/Snake.cpp -o CMakeFiles/Nibbler.dir/Snake.cpp.s

CMakeFiles/Nibbler.dir/GameBoard.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/GameBoard.cpp.o: GameBoard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Nibbler.dir/GameBoard.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/GameBoard.cpp.o -c /Users/kpshenyc/nibbler/mergedClientServer/GameBoard.cpp

CMakeFiles/Nibbler.dir/GameBoard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/GameBoard.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kpshenyc/nibbler/mergedClientServer/GameBoard.cpp > CMakeFiles/Nibbler.dir/GameBoard.cpp.i

CMakeFiles/Nibbler.dir/GameBoard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/GameBoard.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kpshenyc/nibbler/mergedClientServer/GameBoard.cpp -o CMakeFiles/Nibbler.dir/GameBoard.cpp.s

CMakeFiles/Nibbler.dir/ComputerController.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/ComputerController.cpp.o: ComputerController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Nibbler.dir/ComputerController.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/ComputerController.cpp.o -c /Users/kpshenyc/nibbler/mergedClientServer/ComputerController.cpp

CMakeFiles/Nibbler.dir/ComputerController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/ComputerController.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kpshenyc/nibbler/mergedClientServer/ComputerController.cpp > CMakeFiles/Nibbler.dir/ComputerController.cpp.i

CMakeFiles/Nibbler.dir/ComputerController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/ComputerController.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kpshenyc/nibbler/mergedClientServer/ComputerController.cpp -o CMakeFiles/Nibbler.dir/ComputerController.cpp.s

CMakeFiles/Nibbler.dir/DLLHandler.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/DLLHandler.cpp.o: DLLHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Nibbler.dir/DLLHandler.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/DLLHandler.cpp.o -c /Users/kpshenyc/nibbler/mergedClientServer/DLLHandler.cpp

CMakeFiles/Nibbler.dir/DLLHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/DLLHandler.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kpshenyc/nibbler/mergedClientServer/DLLHandler.cpp > CMakeFiles/Nibbler.dir/DLLHandler.cpp.i

CMakeFiles/Nibbler.dir/DLLHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/DLLHandler.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kpshenyc/nibbler/mergedClientServer/DLLHandler.cpp -o CMakeFiles/Nibbler.dir/DLLHandler.cpp.s

CMakeFiles/Nibbler.dir/main.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Nibbler.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/main.cpp.o -c /Users/kpshenyc/nibbler/mergedClientServer/main.cpp

CMakeFiles/Nibbler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kpshenyc/nibbler/mergedClientServer/main.cpp > CMakeFiles/Nibbler.dir/main.cpp.i

CMakeFiles/Nibbler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kpshenyc/nibbler/mergedClientServer/main.cpp -o CMakeFiles/Nibbler.dir/main.cpp.s

# Object files for target Nibbler
Nibbler_OBJECTS = \
"CMakeFiles/Nibbler.dir/Server.cpp.o" \
"CMakeFiles/Nibbler.dir/ClientController.cpp.o" \
"CMakeFiles/Nibbler.dir/Snake.cpp.o" \
"CMakeFiles/Nibbler.dir/GameBoard.cpp.o" \
"CMakeFiles/Nibbler.dir/ComputerController.cpp.o" \
"CMakeFiles/Nibbler.dir/DLLHandler.cpp.o" \
"CMakeFiles/Nibbler.dir/main.cpp.o"

# External object files for target Nibbler
Nibbler_EXTERNAL_OBJECTS =

Nibbler: CMakeFiles/Nibbler.dir/Server.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/ClientController.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/Snake.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/GameBoard.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/ComputerController.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/DLLHandler.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/main.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/build.make
Nibbler: CMakeFiles/Nibbler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Nibbler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Nibbler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Nibbler.dir/build: Nibbler

.PHONY : CMakeFiles/Nibbler.dir/build

CMakeFiles/Nibbler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Nibbler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Nibbler.dir/clean

CMakeFiles/Nibbler.dir/depend:
	cd /Users/kpshenyc/nibbler/mergedClientServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kpshenyc/nibbler/mergedClientServer /Users/kpshenyc/nibbler/mergedClientServer /Users/kpshenyc/nibbler/mergedClientServer /Users/kpshenyc/nibbler/mergedClientServer /Users/kpshenyc/nibbler/mergedClientServer/CMakeFiles/Nibbler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Nibbler.dir/depend

