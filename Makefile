-include version # Checks for a version file and builds one if it cannot find it, I want to automate versioning at some point.
-include settings.mk # Checks for a user settings file for compiling with settings such as "PRETTY_COLORS"

PROGRAM_NAME	:= ANSI

# Checking to see if we are using the cmd shell or UNIX shell
ifeq ($(OS) $(lastword $(notdir $(MAKE))),Windows_NT mingw32-make.exe)
override CMD_SHELL := 1
else # ifneq ($(OS) $(notdir $(MAKE)),Windows_NT mingw32-make.exe)
override CMD_SHELL := 0
endif # ifeq ($(OS) $(notdir $(MAKE)),Windows_NT mingw32-make.exe)

# Functions
    # Remove the first item from a set
override remove_first		= $(filter-out $(firstword $1),$1)
    # Locate all files in the folder in param 1 matching the search strings of param 2
override locate_files		= $(wildcard $(foreach search,$2,$1/$(search)))
    # Locate all folders in the folder of param 1
override locate_folders		= $(filter-out $1, $(foreach folder,$(dir $(wildcard $1/*/)),$(folder:%/=%)))
    # Recursively locate all files in the folder in param 1 matching the search strings of param 2
override rwildcard			= $(strip $(foreach directory,$(call locate_folders, $1),$(call rwildcard,$(directory),$2)) $(call locate_files,$1,$2))
    # Recursively locate all folders in the folder of param 1
override rlocate_folders	= $(strip $(foreach directory,$(call locate_folders, $1),$(call rlocate_folders,$(directory)) $(directory)))
    # Splits the incoming string around spaces and echos each on a new line
override echo_each			= $(foreach str,$1,${\n}$(ECHO_DISABLER)echo $(str))
    # Gets only the unique instances in a set
override unique				= $(if $1,$(firstword $1) $(call unique,$(call remove_first,$1)))
    # Matches any strings in the set of parameter 1 performing replacements based on the replacement functions (=) of param 2
override update_any			= $(if $2,$(call update_any,$(1:$(firstword $2)),$(call remove_first,$2)),$1)

ifdef FULL_FILEPATHS # Specializations of the print_files function based on whether or not we want to print them with full filepaths!
override print_files=$(call echo_each,$1)
override print_file=$1
else # ifndef FULL_FILEPATHS
override print_files=$(call echo_each,$(notdir $1))
override print_file=$(notdir $1)
endif # ifdef FULL_FILEPATHS

define \n # Newline character for usage


endef

ifdef ABSOLUTE_PATHS # Allows us to use the absolute paths instead of relative paths
# Absolute path to current directory
override BASE_DIR		:= $(CURDIR)/
else
# Relative pathing from current directory
override BASE_DIR		:=
endif # ifdef ABSOLUTE_PATHS

# Working folders
override DEPEND_DIR			:= $(BASE_DIR)dependencies
override FIRST_PARTY		:= $(BASE_DIR)firstparty
override THIRD_PARTY		:= $(BASE_DIR)thirdparty
override LIB_IN_DIR			:= $(BASE_DIR)lib
override DLL_IN_DIR			:= $(BASE_DIR)libexc
override SOURCE_DIR			:= $(BASE_DIR)src
override TEST_DRIVER_DIR	:= $(SOURCE_DIR)/tests
override BUILD_DIR			:= $(BASE_DIR)bin
override TEST_DIR			:= $(BUILD_DIR)/test
override OBJECT_DIR			:= $(BUILD_DIR)/objects
override HPP_OUT_DIR		:= $(BASE_DIR)include
override LIB_OUT_DIR		:= $(BUILD_DIR)/lib
override DLL_OUT_DIR		:= $(BUILD_DIR)/libexc
override DLL_OBJECT_DIR		:= $(DLL_OUT_DIR)/objects

override SOURCE_DIRS		:= $(call rlocate_folders,$(SOURCE_DIR))
override DEPEND_DIRS		:= $(patsubst $(SOURCE_DIR)%,$(DEPEND_DIR)%,$(SOURCE_DIRS))
override OBJECT_DIRS		:= $(patsubst $(SOURCE_DIR)%,$(OBJECT_DIR)%,$(SOURCE_DIRS))
override HPP_OUT_DIRS		:= $(filter-out $(patsubst $(SOURCE_DIR)%,$(HPP_OUT_DIR)%,$(TEST_DRIVER_DIR)),$(patsubst $(SOURCE_DIR)%,$(HPP_OUT_DIR)%,$(SOURCE_DIRS)))
override DLL_OBJECT_DIRS	:= $(patsubst $(SOURCE_DIR)%,$(DLL_OBJECT_DIR)%,$(SOURCE_DIRS))

# Since directories do not have files associated with them, make will have some errors with the rules we base around directories, so we mark them as phony using this variable:
override DIRECTORIES := $(DEPEND_DIR) $(FIRST_PARTY) $(THIRD_PARTY) $(LIB_IN_DIR) $(SOURCE_DIR) $(BUILD_DIR) $(TEST_DIR) $(OBJECT_DIR) $(HPP_OUT_DIR) $(LIB_OUT_DIR) $(DLL_OUT_DIR) $(DLL_OBJECT_DIR) $(SOURCE_DIRS) $(DEPEND_DIRS) $(OBJECT_DIRS) $(HPP_OUT_DIRS) $(DLL_OBJECT_DIRS)

# Automatically found imports
override FIRST_HPPS		:= $(call rwildcard,$(FIRST_PARTY),*.hpp *.h)
override THIRD_HPPS		:= $(call rwildcard,$(THIRD_PARTY),*.hpp *.h)
override IMPORT_LIBS	:= $(call rwildcard,$(LIB_IN_DIR),*.lai *.la *.a *.lib)
override IMPORT_DLLS	:= $(call rwildcard,$(DLL_IN_DIR),*.dll *.dylib *.so)

# C++ compiler and flags
    # g++ compiler or we can use Clang or MSVC
CXX						= g++
    # gdb debugger for C++
DEBUG					= gdb
    # Add the debugging flag
CXX_FLAGS			   +=
    # Version 20
override CXX_VERSION	= -std=c++20
    # Compiler warning levels
WARNINGS				= -Wall -Wpedantic -Wextra
    # Include folder for the program
INCLUDE_VARS		   += $(THIRD_PARTY) $(FIRST_PARTY)
override INCLUDES	   := $(foreach include,$(INCLUDE_VARS),-I"$(include)")
    # Library archives/folders for the program
ARCHIVE_VARS		   += $(LIB_IN_DIR)
override ARCHIVES	   := $(foreach library,$(ARCHIVE_VARS),-L"$(library)")
    # Libraries for the program
LIBRARY_VARS		   := $(call update_any,$(IMPORT_LIBS),lib/lib%.lai=% lib/lib%.la=% lib/lib%.a=% lib/%.lib=%)
    # External libraries we need
LIBRARY_VARS		   +=
override LIBRARIES	   := $(foreach archive,$(LIBRARY_VARS),-l"$(archive)")
    # Defined variables for the program, NOTE: we NEED to tell GLFW to not dynamically load Vulkan at runtime.
DEFINE_VARS			   :=
override DEFINES	   := $(foreach define,$(DEFINE_VARS),-D$(define))
    # Compiler libraries we want to statically link so we don't need to ship them.
STATIC_VARS			   := stdc++ gcc
override STATIC_LIBS   := $(foreach static,$(STATIC_VARS),-static-lib$(static)) -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic

# Files
  # File extensions (if needed)
override OBJECT_EXT			= .obj
override CODE_EXT			= .cpp
override HEADER_EXT			= .hpp .h
override DEPENDENCY_EXT		= .mk

  # Code files
    # Sees all .cpp, .hpp, and .h files in our source directory
ALL_FILES 		:= $(call rwildcard,$(SOURCE_DIR),*$(CODE_EXT) $(foreach header_ext,$(HEADER_EXT),*$(header_ext)))
    # Grabs only the .cpp files
CXX_FILES 		:= $(filter %$(CODE_EXT),$(ALL_FILES))
    # Grabs only the .h and .hpp files
HEADER_FILES	:= $(filter $(foreach header_ext,$(HEADER_EXT),%$(header_ext)),$(ALL_FILES))
    # Assume no files are extra
EXTRA_FILES	 	:=
    # All driver files found
TESTER_FILES 	:= $(call rwildcard,$(TEST_DRIVER_DIR),*$(CODE_EXT))
    # Isolate the build driver, since it is what is used when building the whole program.
BUILD_DRIVER	:= $(if $(DRIVER_NAME),$(SOURCE_DIR)/$(DRIVER_NAME)$(CODE_EXT))
    # All drivers
DRIVERS			:= $(BUILD_DRIVER) $(TESTER_FILES)

  # Object files
    # Testing we allow for some of the files to be extra (marked with EXTRA_FILES)
TEST_FILES 				:= $(filter-out $(DRIVERS) $(EXTRA_FILES),$(CXX_FILES))
    # When building DLLs we want all files except whatever our driver is
DLL_BUILD_FILES 		:= $(TEST_FILES)
    # When building a full program, we want all files, so it will just match the CXX files
override BUILD_FILES 	:= $(TEST_FILES) $(BUILD_DRIVER)
    # Each .cpp file will be compiled into its respective .obj file
override CXX_OBJECTS 	:= $(CXX_FILES:$(SOURCE_DIR)%$(CODE_EXT)=$(OBJECT_DIR)%$(OBJECT_EXT))
    # DLL objects for building the dlls
override DLL_OBJECTS 	:= $(DLL_BUILD_FILES:$(SOURCE_DIR)%$(CODE_EXT)=$(DLL_OBJECT_DIR)%$(OBJECT_EXT))
    # Drivers for the DLLs which are separate from other drivers
override DLL_DRIVERS	:= $(TESTER_FILES:$(SOURCE_DIR)%$(CODE_EXT)=$(DLL_OBJECT_DIR)%$(OBJECT_EXT))
    # Test objects for building tests
override TEST_OBJECTS 	:= $(TEST_FILES:$(SOURCE_DIR)%$(CODE_EXT)=$(OBJECT_DIR)%$(OBJECT_EXT))
    # Drivers specific to test runs
override TEST_DRIVERS	:= $(TESTER_FILES:$(SOURCE_DIR)%$(CODE_EXT)=$(OBJECT_DIR)%$(OBJECT_EXT))
    # Build objects for building releases
override BUILD_OBJECTS 	:= $(BUILD_FILES:$(SOURCE_DIR)%$(CODE_EXT)=$(OBJECT_DIR)%$(OBJECT_EXT))
    # Each .cpp file needs a .mk file for its .obj file's dependencies
override DEPENDENCIES 	:= $(CXX_FILES:$(SOURCE_DIR)%$(CODE_EXT)=$(DEPEND_DIR)%$(DEPENDENCY_EXT))
    # All exported headers held here to help with the copy command
override EXPORT_HEADERS	:= $(HEADER_FILES:$(SOURCE_DIR)%=$(HPP_OUT_DIR)%)

  # Output files
    # Name of the output file used for the DLL, LIB, and EXE files
override OUTPUT_NAME	= $(PROGRAM_NAME)-$(VERSION)
    # Build executable output file
override BUILD_EXE		= $(OUTPUT_NAME).exe
    # Test executable output file
override TEST_EXE_BASE	= $(PROGRAM_NAME)-$(TEST_VERSION)
    # DLL output file
override DLL_OUT_FILE	= $(PROGRAM_NAME).dll
    # DLL output file and directory
override BUILT_DLL_OUT	= $(DLL_OUT_DIR)/$(DLL_OUT_FILE)
    # Library output file
override LIB_OUT_FILE	= lib$(DLL_OUT_FILE).a
    # Library output file and directory
override BUILT_LIB_OUT	= $(LIB_OUT_DIR)/$(LIB_OUT_FILE)
    # Executable basenames for all drivers
override TEST_EXES		= $(TESTER_FILES:$(TEST_DRIVER_DIR)/%$(CODE_EXT)=$(TEST_EXE_BASE)-%.exe)
    # Primary build test
override BUILD_TEST		= $(if $(BUILD_DRIVER),$(TEST_DIR)/$(TEST_EXE_BASE).exe)
    # Full test set executable paths
override TESTS			= $(foreach test,$(TEST_EXES),$(TEST_DIR)/$(test)) $(BUILD_TEST)
    # Full dll test set executable paths
override DLL_TESTS		= $(foreach dll_test,$(TEST_EXES),$(DLL_OUT_DIR)/$(dll_test))

# For more information on how to build basic DLLs you can go to the site I was following when setting this up:
# https://www.transmissionzero.co.uk/computing/building-dlls-with-mingw/
# There is also a more advanced page too

# ASCII Escape codes for pretty colors when compiling
ifdef PRETTY_COLORS # Only set up ANSI escape codes if your make will not force the ';' to be a delimiter

# Escape character needed
override ESCAPE_CHARACTER := 

ifeq ($(CMD_SHELL),1)
override ASCII_SEPARATOR := ;
else # Using Unix/Posix shell (We have to escape the ';')
override ASCII_SEPARATOR := \;
endif # ifeq ($(CMD_SHELL),1)

# Normal
  # Foreground
override TEXT_BLACK				= $(ESCAPE_CHARACTER)[30m
override TEXT_WHITE				= $(ESCAPE_CHARACTER)[37m
override TEXT_RED				= $(ESCAPE_CHARACTER)[31m
override TEXT_YELLOW			= $(ESCAPE_CHARACTER)[33m
override TEXT_GREEN				= $(ESCAPE_CHARACTER)[32m
override TEXT_CYAN				= $(ESCAPE_CHARACTER)[36m
override TEXT_BLUE				= $(ESCAPE_CHARACTER)[34m
override TEXT_MAGENTA			= $(ESCAPE_CHARACTER)[35m
override TEXT_RESET				= $(ESCAPE_CHARACTER)[39m

  # Background
override BACK_BLACK				= $(ESCAPE_CHARACTER)[40m
override BACK_WHITE				= $(ESCAPE_CHARACTER)[47m
override BACK_RED				= $(ESCAPE_CHARACTER)[41m
override BACK_YELLOW			= $(ESCAPE_CHARACTER)[43m
override BACK_GREEN				= $(ESCAPE_CHARACTER)[42m
override BACK_CYAN				= $(ESCAPE_CHARACTER)[46m
override BACK_BLUE				= $(ESCAPE_CHARACTER)[44m
override BACK_MAGENTA			= $(ESCAPE_CHARACTER)[45m
override BACK_RESET				= $(ESCAPE_CHARACTER)[49m

# Bright
  # Foreground
override TEXT_BRIGHT_BLACK		= $(ESCAPE_CHARACTER)[90m
override TEXT_BRIGHT_WHITE		= $(ESCAPE_CHARACTER)[97m
override TEXT_BRIGHT_RED		= $(ESCAPE_CHARACTER)[91m
override TEXT_BRIGHT_YELLOW		= $(ESCAPE_CHARACTER)[93m
override TEXT_BRIGHT_GREEN		= $(ESCAPE_CHARACTER)[92m
override TEXT_BRIGHT_CYAN		= $(ESCAPE_CHARACTER)[96m
override TEXT_BRIGHT_BLUE		= $(ESCAPE_CHARACTER)[94m
override TEXT_BRIGHT_MAGENTA	= $(ESCAPE_CHARACTER)[95m

  # Background
override BACK_BRIGHT_BLACK		= $(ESCAPE_CHARACTER)[100m
override BACK_BRIGHT_WHITE		= $(ESCAPE_CHARACTER)[107m
override BACK_BRIGHT_RED		= $(ESCAPE_CHARACTER)[101m
override BACK_BRIGHT_YELLOW		= $(ESCAPE_CHARACTER)[103m
override BACK_BRIGHT_GREEN		= $(ESCAPE_CHARACTER)[102m
override BACK_BRIGHT_CYAN		= $(ESCAPE_CHARACTER)[106m
override BACK_BRIGHT_BLUE		= $(ESCAPE_CHARACTER)[104m
override BACK_BRIGHT_MAGENTA	= $(ESCAPE_CHARACTER)[105m

# Completely reset
override RESET 					= $(ESCAPE_CHARACTER)[m

endif # ifdef PRETTY_COLORS

ifdef ECHO_ON # If echo is turned on, remove the disabler
override ECHO_DISABLER :=
else
override ECHO_DISABLER := @
endif # ifdef ECHO_ON

# Preset outputs for the terminal
SUCCESS = $(TEXT_GREEN)Success!$(TEXT_RESET)

# Necessary things for compiled code
PROGRAM_ARGS := # No args necessary yet!

.NOTINTERMEDIATE :
.PHONY : clean default run_dll run_build run_test run_debug_dll run_debug_build run_debug_test view_files view_directories view_externals make_dll_exe make_build make_dll make_test copy_headers $(DIRECTORIES)

include $(DEPENDENCIES) # Automatically builds all dependencies at runtime

# TODO: Need to add either a way to use a .hpp file to get the major, minor, patch, and test version
# OR need to add a makefile that tracks them, updates itself, and then we can send the version to the compiler with the -D flag

run_build : $(BUILD_DIR)/$(BUILD_EXE)
	$(ECHO_DISABLER)echo $(TEXT_CYAN)We have an executable, running the current build...$(TEXT_RESET)
	$(ECHO_DISABLER)$(BUILD_DIR)/$(BUILD_EXE) $(PROGRAM_ARGS)
	$(ECHO_DISABLER)echo $(SUCCESS)

run_tests : make_tests
	$(ECHO_DISABLER)echo $(TEXT_CYAN)Found the executable, running tests...$(TEXT_RESET)
	$(foreach test,$(TESTS),$(ECHO_DISABLER)$(test)${\n})
	$(ECHO_DISABLER)echo $(SUCCESS)

run_dll_tests : $(DLL_TESTS)
	$(ECHO_DISABLER)echo $(TEXT_CYAN)Executable located, running the program...$(TEXT_RESET)
	$(foreach test,$(DLL_TESTS),$(ECHO_DISABLER)$(test)${\n})
	$(ECHO_DISABLER)echo $(SUCCESS)

run_debug_build : $(BUILD_DIR)/$(BUILD_EXE)
	$(ECHO_DISABLER)echo $(TEXT_CYAN)We have an executable, running the current build...$(TEXT_RESET)
	$(ECHO_DISABLER)$(DEBUG) $(BUILD_DIR)/$(BUILD_EXE) --args $(PROGRAM_ARGS)
	$(ECHO_DISABLER)echo $(SUCCESS)

run_debug_tests : $(TESTS)
	$(ECHO_DISABLER)echo $(TEXT_CYAN)Found the executable, beginning a test run...$(TEXT_RESET)
	$(foreach test,$(TESTS),$(ECHO_DISABLER)$(DEBUG) $(test)${\n})
	$(ECHO_DISABLER)echo $(SUCCESS)

run_debug_dll_tests : $(DLL_TESTS)
	$(ECHO_DISABLER)echo $(TEXT_CYAN)Executable located, running the program...$(TEXT_RESET)
	$(foreach test,$(DLL_TESTS),$(ECHO_DISABLER)$(DEBUG) $(test)${\n})
	$(ECHO_DISABLER)echo $(SUCCESS)

make_dll_tests : $(DLL_TESTS) copy_dlls/$(DLL_OUT_DIR)
$(DLL_OUT_DIR)/$(TEST_EXE_BASE)-%.exe : $(BUILT_DLL_OUT) $(DLL_OBJECT_DIR)/tests/%$(OBJECT_EXT) | $(DLL_OUT_DIR)
	$(ECHO_DISABLER)echo $(TEXT_BLUE)Dynamic library is up to date, building an executable!$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(@:$(DLL_OUT_DIR)/$(TEST_EXE_BASE)-%.exe=$(DLL_OBJECT_DIR)/tests/%$(OBJECT_EXT)) $(ARCHIVES) -L"$(LIB_OUT_DIR)" $(LIBRARIES) -l"$(DLL_OUT_FILE)" $(STATIC_LIBS) -o $@
	$(ECHO_DISABLER)echo $(SUCCESS)

make_dll $(BUILT_DLL_OUT) : $(DLL_OBJECTS) | $(DLL_OUT_DIR) $(HPP_OUT_DIR) $(LIB_OUT_DIR) copy_headers
	$(ECHO_DISABLER)echo $(TEXT_BLUE)All object files are up to date, building the library!$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(DLL_OBJECTS) -o $(BUILT_DLL_OUT) -s -shared -Wl,--subsystem,windows,--out-implib,$(BUILT_LIB_OUT)
	$(ECHO_DISABLER)echo $(SUCCESS)

copy_headers : $(HPP_OUT_DIR) $(HPP_OUT_DIRS)
ifeq ($(CMD_SHELL),1) # Note that not only do we have to use "copy" for windows, but it's also one of the only 2 functions in windows that REQUIRES backslashes...
	$(if $(HEADER_FILES),$(foreach header,$(HEADER_FILES),$(ECHO_DISABLER)copy /Y $(subst /,\,$(header) $(header:$(SOURCE_DIR)%=$(HPP_OUT_DIR)%)) >NUL${\n}))
else # Using Unix/Posix shell
	$(if $(HEADER_FILES),$(foreach header,$(HEADER_FILES),$(ECHO_DISABLER)cp /Y $(header) $(header:$(SOURCE_DIR)%=$(HPP_OUT_DIR)%) >NUL${\n}))
endif # ifeq ($(CMD_SHELL),1)
	$(ECHO_DISABLER)echo $(TEXT_GREEN)Copied over all headers from $(TEXT_WHITE)"$(SOURCE_DIR)"$(TEXT_GREEN) to $(TEXT_YELLOW)"$(HPP_OUT_DIR)"$(TEXT_GREEN)!$(TEXT_RESET)

make_build $(BUILD_DIR)/$(BUILD_EXE) : $(BUILD_OBJECTS) | $(BUILD_DIR) copy_dlls/$(BUILD_DIR)
	$(ECHO_DISABLER)echo $(TEXT_BLUE)All object files are up to date, building test file!$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(BUILD_OBJECTS) $(ARCHIVES) $(LIBRARIES) $(STATIC_LIBS) -o $(BUILD_DIR)/$(BUILD_EXE)
	$(ECHO_DISABLER)echo $(SUCCESS)

make_tests : $(TESTS) copy_dlls/$(TEST_DIR)
$(TEST_DIR)/$(TEST_EXE_BASE)-%.exe : $(TEST_OBJECTS) $(OBJECT_DIR)/tests/%$(OBJECT_EXT) | $(TEST_DIR)
	$(ECHO_DISABLER)echo $(TEXT_BLUE)All object files are up to date, building test file!$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(TEST_OBJECTS) $(@:$(TEST_DIR)/$(TEST_EXE_BASE)-%.exe=$(OBJECT_DIR)/tests/%$(OBJECT_EXT)) $(ARCHIVES) $(LIBRARIES) $(STATIC_LIBS) -o $@
	$(ECHO_DISABLER)echo $(SUCCESS)

copy_dlls/% : %
ifeq ($(CMD_SHELL),1) # Note that not only do we have to use "copy" for windows, but it's also one of the only 2 functions in windows that REQUIRES backslashes...
	$(if $(IMPORT_DLLS),$(foreach dll,$(IMPORT_DLLS),$(ECHO_DISABLER)copy /Y $(subst /,\,$(dll) $(dll:$(DLL_IN_DIR)%=$<%)) >NUL${\n}))
else # Using Unix/Posix shell
	$(if $(IMPORT_DLLS),$(foreach dll,$(IMPORT_DLLS),$(ECHO_DISABLER)cp /Y $(dll) $(dll:$(DLL_IN_DIR)%=$<%) >NUL${\n}))
endif # ifeq ($(CMD_SHELL),1)
	$(ECHO_DISABLER)echo $(TEXT_GREEN)Copied over all dlls from $(TEXT_MAGENTA)"$(DLL_IN_DIR)"$(TEXT_GREEN) to $(TEXT_YELLOW)"$<"$(TEXT_GREEN)!$(TEXT_RESET)

$(BUILD_TEST) : $(BUILD_DRIVER:$(SOURCE_DIR)%$(CODE_EXT)=$(OBJECT_DIR)%$(OBJECT_EXT)) $(TEST_OBJECTS) | $(TEST_DIR)
	$(ECHO_DISABLER)echo $(TEXT_BLUE)All object files are up to date, building test build file!$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(TEST_OBJECTS) $< $(ARCHIVES) $(LIBRARIES) -o $@
	$(ECHO_DISABLER)echo $(SUCCESS)

$(DLL_OBJECT_DIR)/tests/%$(OBJECT_EXT) : $(TEST_DRIVER_DIR)/%$(CODE_EXT) | $(DLL_OBJECT_DIR) $(DLL_OBJECT_DIR)/tests
	$(ECHO_DISABLER)echo $(TEXT_YELLOW)Building the DLL driver object file $(TEXT_BLUE)"$(call print_file,$@)"$(TEXT_YELLOW)...$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(CXX_VERSION) -c $(INCLUDES) -I"$(HPP_OUT_DIR)" $< $(CXX_FLAGS) $(DEFINES) -DMEM_DLL_IMPORT $(WARNINGS) -o $@
	$(ECHO_DISABLER)echo $(SUCCESS)

$(DLL_OBJECT_DIR)/%$(OBJECT_EXT) : $(SOURCE_DIR)/%$(CODE_EXT) | $(DLL_OBJECT_DIR) $(DLL_OBJECT_DIRS)
	$(ECHO_DISABLER)echo $(TEXT_YELLOW)Building the DLL object file $(TEXT_BLUE)"$(call print_file,$@)"$(TEXT_YELLOW)...$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(CXX_VERSION) -c $(INCLUDES) $< $(CXX_FLAGS) $(DEFINES) -DTEST_DLL -DMEM_DLL_EXPORT $(WARNINGS) -o $@
	$(ECHO_DISABLER)echo $(SUCCESS)

$(OBJECT_DIR)/%$(OBJECT_EXT) : $(SOURCE_DIR)/%$(CODE_EXT) | $(OBJECT_DIR) $(OBJECT_DIRS)
	$(ECHO_DISABLER)echo $(TEXT_YELLOW)Building the object file $(TEXT_BLUE)"$(call print_file,$@)"$(TEXT_YELLOW)...$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(CXX_VERSION) -c $(INCLUDES) $< $(CXX_FLAGS) $(DEFINES) $(WARNINGS) -o $@
	$(ECHO_DISABLER)echo $(SUCCESS)

$(DEPEND_DIR)/%$(DEPENDENCY_EXT) : $(SOURCE_DIR)/%$(CODE_EXT) | $(DEPEND_DIR) $(DEPEND_DIRS)
	$(ECHO_DISABLER)echo $(TEXT_MAGENTA)The dependencies of $(TEXT_BLUE)"$(call print_file,$<)"$(TEXT_MAGENTA) have been modified, rebuilding them...$(TEXT_RESET)
	$(ECHO_DISABLER)$(CXX) $(CXX_VERSION) $< -MT '$(<:$(SOURCE_DIR)%$(CODE_EXT)=$(OBJECT_DIR)%$(OBJECT_EXT)) $(<:$(SOURCE_DIR)%$(CODE_EXT)=$(DLL_OBJECT_DIR)%$(OBJECT_EXT))' -MM -MF $@
	$(ECHO_DISABLER)echo $(SUCCESS)

ifeq ($(CMD_SHELL),1)
$(DIRECTORIES) :
	$(ECHO_DISABLER)if not exist "$@" mkdir "$@"
else # Using Unix/Posix shell
$(DIRECTORIES) :
	$(ECHO_DISABLER)mkdir -p "$@"
endif # ifeq ($(CMD_SHELL),1)

view_files :
	$(ECHO_DISABLER)echo Printing all project files:		$(TEXT_YELLOW)	$(call print_files,$(ALL_FILES))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all code files:			$(TEXT_YELLOW)	$(call print_files,$(CXX_FILES))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all header files:			$(TEXT_YELLOW)	$(call print_files,$(HEADER_FILES))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all exported header files:$(TEXT_YELLOW)	$(call print_files,$(EXPORT_HEADERS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all C++ test files:		$(TEXT_YELLOW)	$(call print_files,$(TEST_FILES))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all C++ build files:		$(TEXT_YELLOW)	$(call print_files,$(BUILD_FILES))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all C++ test objects:		$(TEXT_BLUE)	$(call print_files,$(TEST_OBJECTS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all C++ build objects:	$(TEXT_BLUE)	$(call print_files,$(BUILD_OBJECTS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing all dependency makefiles:	$(TEXT_RED)		$(call print_files,$(DEPENDENCIES))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing the dll and lib files:	$(TEXT_MAGENTA)	$(call print_files,$(BUILT_DLL_OUT) $(BUILT_LIB_OUT))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Printing the exe files:			$(TEXT_MAGENTA)	$(call print_files,$(BUILD_DIR)/$(BUILD_EXE) $(TESTS) $(DLL_TESTS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)

view_directories :
	$(ECHO_DISABLER)echo Directory structure:
  # Build/bin directory and subfolders
	$(ECHO_DISABLER)echo $(TEXT_CYAN)$(BUILD_DIR)
	$(ECHO_DISABLER)echo $(TEXT_GREEN)$(DLL_OUT_DIR)
	$(ECHO_DISABLER)echo $(TEXT_BLUE)$(DLL_OBJECT_DIR)
	$(call echo_each,$(DLL_OBJECT_DIRS))
	$(ECHO_DISABLER)echo $(TEXT_YELLOW)$(HPP_OUT_DIR)
	$(call echo_each,$(HPP_OUT_DIRS))
	$(ECHO_DISABLER)echo $(TEXT_MAGENTA)$(LIB_OUT_DIR)
	$(call echo_each,$(call rlocate_folders,$(LIB_OUT_DIR)))
	$(ECHO_DISABLER)echo $(TEXT_BLUE)$(OBJECT_DIR)
	$(call echo_each,$(OBJECT_DIRS))
	$(ECHO_DISABLER)echo $(TEXT_GREEN)$(TEST_DIR)
  # Dependency directory and subfolders
	$(ECHO_DISABLER)echo $(TEXT_RED)$(DEPEND_DIR)
	$(call echo_each,$(DEPEND_DIRS))
  # Include import directory and subfolders
	$(ECHO_DISABLER)echo $(TEXT_YELLOW)$(FIRST_PARTY)
	$(call echo_each,$(call rlocate_folders,$(FIRST_PARTY)))
	$(ECHO_DISABLER)echo $(TEXT_YELLOW)$(THIRD_PARTY)
	$(call echo_each,$(call rlocate_folders,$(THIRD_PARTY)))
  # Library import directory and subfolders
	$(ECHO_DISABLER)echo $(TEXT_MAGENTA)$(LIB_IN_DIR)
	$(call echo_each,$(call rlocate_folders,$(LIB_IN_DIR)))
  # DLL import directory and subfolders
	$(ECHO_DISABLER)echo $(TEXT_MAGENTA)$(DLL_IN_DIR)
	$(call echo_each,$(call rlocate_folders,$(DLL_IN_DIR)))
  # Source directory and subfolders
	$(ECHO_DISABLER)echo $(TEXT_WHITE)$(SOURCE_DIR)
	$(call echo_each,$(SOURCE_DIRS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)

  # This one command can print ALL directories, even if they are updated!
	$(ECHO_DISABLER)echo All existing directories:
	$(ECHO_DISABLER)$(call echo_each,$(call rlocate_folders,.))
	$(ECHO_DISABLER)echo $(TEXT_RESET)

view_externals :
	$(ECHO_DISABLER)echo First party headers:			$(TEXT_BRIGHT_YELLOW)	$(call print_files,$(FIRST_HPPS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Third party headers:			$(TEXT_BRIGHT_YELLOW)	$(call print_files,$(THIRD_HPPS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)
	$(ECHO_DISABLER)echo Imported libraries:			$(TEXT_BRIGHT_YELLOW)	$(call print_files,$(IMPORT_LIBS))
	$(ECHO_DISABLER)echo $(TEXT_RESET)

clean :
ifeq ($(CMD_SHELL),1)
	-$(ECHO_DISABLER)rmdir /S /Q bin
	-$(ECHO_DISABLER)rmdir /S /Q dependencies
else # Using Unix/Posix shell
	-$(ECHO_DISABLER)rm -r bin
	-$(ECHO_DISABLER)rm -r dependencies
endif # ifeq ($(CMD_SHELL),1)