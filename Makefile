# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/marek/studia/semestr_5/sk2/projekt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marek/studia/semestr_5/sk2/projekt

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/marek/studia/semestr_5/sk2/projekt/CMakeFiles /home/marek/studia/semestr_5/sk2/projekt/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/marek/studia/semestr_5/sk2/projekt/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named kahut

# Build rule for target.
kahut: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 kahut
.PHONY : kahut

# fast build rule for target.
kahut/fast:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/build
.PHONY : kahut/fast

#=============================================================================
# Target rules for targets named kahut_autogen

# Build rule for target.
kahut_autogen: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 kahut_autogen
.PHONY : kahut_autogen

# fast build rule for target.
kahut_autogen/fast:
	$(MAKE) -f CMakeFiles/kahut_autogen.dir/build.make CMakeFiles/kahut_autogen.dir/build
.PHONY : kahut_autogen/fast

Client.o: Client.cpp.o

.PHONY : Client.o

# target to build an object file
Client.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Client.cpp.o
.PHONY : Client.cpp.o

Client.i: Client.cpp.i

.PHONY : Client.i

# target to preprocess a source file
Client.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Client.cpp.i
.PHONY : Client.cpp.i

Client.s: Client.cpp.s

.PHONY : Client.s

# target to generate assembly for a file
Client.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Client.cpp.s
.PHONY : Client.cpp.s

ClientWindow.o: ClientWindow.cpp.o

.PHONY : ClientWindow.o

# target to build an object file
ClientWindow.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/ClientWindow.cpp.o
.PHONY : ClientWindow.cpp.o

ClientWindow.i: ClientWindow.cpp.i

.PHONY : ClientWindow.i

# target to preprocess a source file
ClientWindow.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/ClientWindow.cpp.i
.PHONY : ClientWindow.cpp.i

ClientWindow.s: ClientWindow.cpp.s

.PHONY : ClientWindow.s

# target to generate assembly for a file
ClientWindow.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/ClientWindow.cpp.s
.PHONY : ClientWindow.cpp.s

Question.o: Question.cpp.o

.PHONY : Question.o

# target to build an object file
Question.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Question.cpp.o
.PHONY : Question.cpp.o

Question.i: Question.cpp.i

.PHONY : Question.i

# target to preprocess a source file
Question.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Question.cpp.i
.PHONY : Question.cpp.i

Question.s: Question.cpp.s

.PHONY : Question.s

# target to generate assembly for a file
Question.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Question.cpp.s
.PHONY : Question.cpp.s

Server.o: Server.cpp.o

.PHONY : Server.o

# target to build an object file
Server.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Server.cpp.o
.PHONY : Server.cpp.o

Server.i: Server.cpp.i

.PHONY : Server.i

# target to preprocess a source file
Server.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Server.cpp.i
.PHONY : Server.cpp.i

Server.s: Server.cpp.s

.PHONY : Server.s

# target to generate assembly for a file
Server.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/Server.cpp.s
.PHONY : Server.cpp.s

User.o: User.cpp.o

.PHONY : User.o

# target to build an object file
User.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/User.cpp.o
.PHONY : User.cpp.o

User.i: User.cpp.i

.PHONY : User.i

# target to preprocess a source file
User.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/User.cpp.i
.PHONY : User.cpp.i

User.s: User.cpp.s

.PHONY : User.s

# target to generate assembly for a file
User.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/User.cpp.s
.PHONY : User.cpp.s

UserConnection.o: UserConnection.cpp.o

.PHONY : UserConnection.o

# target to build an object file
UserConnection.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/UserConnection.cpp.o
.PHONY : UserConnection.cpp.o

UserConnection.i: UserConnection.cpp.i

.PHONY : UserConnection.i

# target to preprocess a source file
UserConnection.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/UserConnection.cpp.i
.PHONY : UserConnection.cpp.i

UserConnection.s: UserConnection.cpp.s

.PHONY : UserConnection.s

# target to generate assembly for a file
UserConnection.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/UserConnection.cpp.s
.PHONY : UserConnection.cpp.s

kahut_autogen/mocs_compilation.o: kahut_autogen/mocs_compilation.cpp.o

.PHONY : kahut_autogen/mocs_compilation.o

# target to build an object file
kahut_autogen/mocs_compilation.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/kahut_autogen/mocs_compilation.cpp.o
.PHONY : kahut_autogen/mocs_compilation.cpp.o

kahut_autogen/mocs_compilation.i: kahut_autogen/mocs_compilation.cpp.i

.PHONY : kahut_autogen/mocs_compilation.i

# target to preprocess a source file
kahut_autogen/mocs_compilation.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/kahut_autogen/mocs_compilation.cpp.i
.PHONY : kahut_autogen/mocs_compilation.cpp.i

kahut_autogen/mocs_compilation.s: kahut_autogen/mocs_compilation.cpp.s

.PHONY : kahut_autogen/mocs_compilation.s

# target to generate assembly for a file
kahut_autogen/mocs_compilation.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/kahut_autogen/mocs_compilation.cpp.s
.PHONY : kahut_autogen/mocs_compilation.cpp.s

main_app.o: main_app.cpp.o

.PHONY : main_app.o

# target to build an object file
main_app.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/main_app.cpp.o
.PHONY : main_app.cpp.o

main_app.i: main_app.cpp.i

.PHONY : main_app.i

# target to preprocess a source file
main_app.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/main_app.cpp.i
.PHONY : main_app.cpp.i

main_app.s: main_app.cpp.s

.PHONY : main_app.s

# target to generate assembly for a file
main_app.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/main_app.cpp.s
.PHONY : main_app.cpp.s

serverwindow.o: serverwindow.cpp.o

.PHONY : serverwindow.o

# target to build an object file
serverwindow.cpp.o:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/serverwindow.cpp.o
.PHONY : serverwindow.cpp.o

serverwindow.i: serverwindow.cpp.i

.PHONY : serverwindow.i

# target to preprocess a source file
serverwindow.cpp.i:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/serverwindow.cpp.i
.PHONY : serverwindow.cpp.i

serverwindow.s: serverwindow.cpp.s

.PHONY : serverwindow.s

# target to generate assembly for a file
serverwindow.cpp.s:
	$(MAKE) -f CMakeFiles/kahut.dir/build.make CMakeFiles/kahut.dir/serverwindow.cpp.s
.PHONY : serverwindow.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... kahut"
	@echo "... kahut_autogen"
	@echo "... Client.o"
	@echo "... Client.i"
	@echo "... Client.s"
	@echo "... ClientWindow.o"
	@echo "... ClientWindow.i"
	@echo "... ClientWindow.s"
	@echo "... Question.o"
	@echo "... Question.i"
	@echo "... Question.s"
	@echo "... Server.o"
	@echo "... Server.i"
	@echo "... Server.s"
	@echo "... User.o"
	@echo "... User.i"
	@echo "... User.s"
	@echo "... UserConnection.o"
	@echo "... UserConnection.i"
	@echo "... UserConnection.s"
	@echo "... kahut_autogen/mocs_compilation.o"
	@echo "... kahut_autogen/mocs_compilation.i"
	@echo "... kahut_autogen/mocs_compilation.s"
	@echo "... main_app.o"
	@echo "... main_app.i"
	@echo "... main_app.s"
	@echo "... serverwindow.o"
	@echo "... serverwindow.i"
	@echo "... serverwindow.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
