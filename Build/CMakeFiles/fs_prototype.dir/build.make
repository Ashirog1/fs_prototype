# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Hiep\code\fs_prototype

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Hiep\code\fs_prototype\Build

# Include any dependencies generated for this target.
include CMakeFiles/fs_prototype.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fs_prototype.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fs_prototype.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fs_prototype.dir/flags.make

CMakeFiles/fs_prototype.dir/main.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/main.cpp.obj: D:/Hiep/code/fs_prototype/main.cpp
CMakeFiles/fs_prototype.dir/main.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fs_prototype.dir/main.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/main.cpp.obj -MF CMakeFiles\fs_prototype.dir\main.cpp.obj.d -o CMakeFiles\fs_prototype.dir\main.cpp.obj -c D:\Hiep\code\fs_prototype\main.cpp

CMakeFiles/fs_prototype.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/main.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\main.cpp > CMakeFiles\fs_prototype.dir\main.cpp.i

CMakeFiles/fs_prototype.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/main.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\main.cpp -o CMakeFiles\fs_prototype.dir\main.cpp.s

CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.obj: D:/Hiep/code/fs_prototype/src/problem/game_board.cpp
CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.obj -MF CMakeFiles\fs_prototype.dir\src\problem\game_board.cpp.obj.d -o CMakeFiles\fs_prototype.dir\src\problem\game_board.cpp.obj -c D:\Hiep\code\fs_prototype\src\problem\game_board.cpp

CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\src\problem\game_board.cpp > CMakeFiles\fs_prototype.dir\src\problem\game_board.cpp.i

CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\src\problem\game_board.cpp -o CMakeFiles\fs_prototype.dir\src\problem\game_board.cpp.s

CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.obj: D:/Hiep/code/fs_prototype/src/search/focal_search.cpp
CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.obj -MF CMakeFiles\fs_prototype.dir\src\search\focal_search.cpp.obj.d -o CMakeFiles\fs_prototype.dir\src\search\focal_search.cpp.obj -c D:\Hiep\code\fs_prototype\src\search\focal_search.cpp

CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\src\search\focal_search.cpp > CMakeFiles\fs_prototype.dir\src\search\focal_search.cpp.i

CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\src\search\focal_search.cpp -o CMakeFiles\fs_prototype.dir\src\search\focal_search.cpp.s

CMakeFiles/fs_prototype.dir/src/heuristics.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/src/heuristics.cpp.obj: D:/Hiep/code/fs_prototype/src/heuristics.cpp
CMakeFiles/fs_prototype.dir/src/heuristics.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/fs_prototype.dir/src/heuristics.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/src/heuristics.cpp.obj -MF CMakeFiles\fs_prototype.dir\src\heuristics.cpp.obj.d -o CMakeFiles\fs_prototype.dir\src\heuristics.cpp.obj -c D:\Hiep\code\fs_prototype\src\heuristics.cpp

CMakeFiles/fs_prototype.dir/src/heuristics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/src/heuristics.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\src\heuristics.cpp > CMakeFiles\fs_prototype.dir\src\heuristics.cpp.i

CMakeFiles/fs_prototype.dir/src/heuristics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/src/heuristics.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\src\heuristics.cpp -o CMakeFiles\fs_prototype.dir\src\heuristics.cpp.s

CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.obj: D:/Hiep/code/fs_prototype/src/search/BoundedFocalSearch.cpp
CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.obj -MF CMakeFiles\fs_prototype.dir\src\search\BoundedFocalSearch.cpp.obj.d -o CMakeFiles\fs_prototype.dir\src\search\BoundedFocalSearch.cpp.obj -c D:\Hiep\code\fs_prototype\src\search\BoundedFocalSearch.cpp

CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\src\search\BoundedFocalSearch.cpp > CMakeFiles\fs_prototype.dir\src\search\BoundedFocalSearch.cpp.i

CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\src\search\BoundedFocalSearch.cpp -o CMakeFiles\fs_prototype.dir\src\search\BoundedFocalSearch.cpp.s

CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.obj: D:/Hiep/code/fs_prototype/src/search/RWFocalSearch.cpp
CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.obj -MF CMakeFiles\fs_prototype.dir\src\search\RWFocalSearch.cpp.obj.d -o CMakeFiles\fs_prototype.dir\src\search\RWFocalSearch.cpp.obj -c D:\Hiep\code\fs_prototype\src\search\RWFocalSearch.cpp

CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\src\search\RWFocalSearch.cpp > CMakeFiles\fs_prototype.dir\src\search\RWFocalSearch.cpp.i

CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\src\search\RWFocalSearch.cpp -o CMakeFiles\fs_prototype.dir\src\search\RWFocalSearch.cpp.s

CMakeFiles/fs_prototype.dir/src/search/utils.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/src/search/utils.cpp.obj: D:/Hiep/code/fs_prototype/src/search/utils.cpp
CMakeFiles/fs_prototype.dir/src/search/utils.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/fs_prototype.dir/src/search/utils.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/src/search/utils.cpp.obj -MF CMakeFiles\fs_prototype.dir\src\search\utils.cpp.obj.d -o CMakeFiles\fs_prototype.dir\src\search\utils.cpp.obj -c D:\Hiep\code\fs_prototype\src\search\utils.cpp

CMakeFiles/fs_prototype.dir/src/search/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/src/search/utils.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\src\search\utils.cpp > CMakeFiles\fs_prototype.dir\src\search\utils.cpp.i

CMakeFiles/fs_prototype.dir/src/search/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/src/search/utils.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\src\search\utils.cpp -o CMakeFiles\fs_prototype.dir\src\search\utils.cpp.s

CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.obj: CMakeFiles/fs_prototype.dir/flags.make
CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.obj: D:/Hiep/code/fs_prototype/src/search/PotentialFocalSearch.cpp
CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.obj: CMakeFiles/fs_prototype.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.obj -MF CMakeFiles\fs_prototype.dir\src\search\PotentialFocalSearch.cpp.obj.d -o CMakeFiles\fs_prototype.dir\src\search\PotentialFocalSearch.cpp.obj -c D:\Hiep\code\fs_prototype\src\search\PotentialFocalSearch.cpp

CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Hiep\code\fs_prototype\src\search\PotentialFocalSearch.cpp > CMakeFiles\fs_prototype.dir\src\search\PotentialFocalSearch.cpp.i

CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Hiep\code\fs_prototype\src\search\PotentialFocalSearch.cpp -o CMakeFiles\fs_prototype.dir\src\search\PotentialFocalSearch.cpp.s

# Object files for target fs_prototype
fs_prototype_OBJECTS = \
"CMakeFiles/fs_prototype.dir/main.cpp.obj" \
"CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.obj" \
"CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.obj" \
"CMakeFiles/fs_prototype.dir/src/heuristics.cpp.obj" \
"CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.obj" \
"CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.obj" \
"CMakeFiles/fs_prototype.dir/src/search/utils.cpp.obj" \
"CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.obj"

# External object files for target fs_prototype
fs_prototype_EXTERNAL_OBJECTS =

fs_prototype.exe: CMakeFiles/fs_prototype.dir/main.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/src/problem/game_board.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/src/search/focal_search.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/src/heuristics.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/src/search/BoundedFocalSearch.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/src/search/RWFocalSearch.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/src/search/utils.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/src/search/PotentialFocalSearch.cpp.obj
fs_prototype.exe: CMakeFiles/fs_prototype.dir/build.make
fs_prototype.exe: CMakeFiles/fs_prototype.dir/linkLibs.rsp
fs_prototype.exe: CMakeFiles/fs_prototype.dir/objects1.rsp
fs_prototype.exe: CMakeFiles/fs_prototype.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Hiep\code\fs_prototype\Build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable fs_prototype.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\fs_prototype.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fs_prototype.dir/build: fs_prototype.exe
.PHONY : CMakeFiles/fs_prototype.dir/build

CMakeFiles/fs_prototype.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\fs_prototype.dir\cmake_clean.cmake
.PHONY : CMakeFiles/fs_prototype.dir/clean

CMakeFiles/fs_prototype.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Hiep\code\fs_prototype D:\Hiep\code\fs_prototype D:\Hiep\code\fs_prototype\Build D:\Hiep\code\fs_prototype\Build D:\Hiep\code\fs_prototype\Build\CMakeFiles\fs_prototype.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fs_prototype.dir/depend

