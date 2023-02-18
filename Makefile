# Define the compiler to use
CC := g++
# Define compiler flags used in all builds
CFLAGS := -std=c++11 -Wall

# Define compiler flags used in debug & release builds
DEBUGFLAGS := -g -O0 -D DEBUG
RELEASEFLAGS := -O3

# Define the name of the output executable
EXC := CoffeeShop

# Define various directories
SRCDIR := src
LIBDIR := libs
OBJDIR := obj
DEPDIR := $(OBJDIR)/deps
RELEASEDIR := release

LIBFILES := TerminalGraphics/TerminalGraphics
INCLUDEDIRS := TerminalGraphics/include

# Create build files in the release directory if that is the make target
ifeq ($(MAKECMDGOALS),release)
	EXC := $(RELEASEDIR)/$(EXC)
	OBJDIR := $(RELEASEDIR)/$(OBJDIR)
	DEPDIR := $(RELEASEDIR)/$(DEPDIR)
endif

# Define a recursive wildcard function to search for source files
# I got this function from https://stackoverflow.com/a/18258352
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2)$(filter $(subst *,%,$2),$d))

# Find source files using the recursive wildcard function
SRCS := $(patsubst $(SRCDIR)/%,%,$(call rwildcard,$(SRCDIR),*.cpp))

# Create a list of subdirectories so that the directory structure can be recreated in the object directory
SUBDIRECTORIES := $(sort $(patsubst %/,%,$(dir $(addprefix $(OBJDIR)/,$(SRCS))))) $(sort $(patsubst %/,%,$(dir $(addprefix $(DEPDIR)/,$(SRCS)))))

# Platform specific things go here
# Detection of platform and archetecture are from https://stackoverflow.com/a/12099167
ifeq ($(OS),Windows_NT)
	CFLAGS += -D WIN32

	EXC := $(EXC).exe
	oslibfiles=$(addsuffix .lib,$1) # Function to convert library files to the format used by the OS
	ospath=$(subst /,\,$1) # Function to convert file paths to the format used by the OS
	MKDIR = mkdir $(call ospath,$@)
define CLEAN = # Here the if function is used to prevent an error caused by attempting to deleting a file that does not exist
$(if $(wildcard $(OBJDIR) $(RELEASEDIR)), rmdir /Q /S $(wildcard $(OBJDIR) $(RELEASEDIR)))
$(if $(wildcard $(EXC)), del $(wildcard $(EXC)))
endef # I can't indent here because make doesn't like it

	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		CFLAGS += -D AMD64 -m64 # Here the extra -m64 flag tells the compiler to compile for 64 bit
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			CFLAGS += -D AMD64 -m64 # Here the extra -m64 flag tells the compiler to compile for 64 bit
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			CFLAGS += -D IA32
		endif
	endif
else
	oslibfiles=$(foreach LIBFILE,$1,$(dir $(LIBFILE))lib$(notdir $(LIBFILE)).a) # Function to convert library files to the format used by the OS
	ospath=$1 # Function to convert file paths to the format used by the OS
	MKDIR = mkdir -p $(call ospath,$@)
	# Here the if function is used to prevent an error caused by attempting to deleting a file that does not exist
	CLEAN = $(if $(wildcard $(OBJDIR) $(RELEASEDIR) $(EXC)), rm -rf $(wildcard $(OBJDIR) $(RELEASEDIR) $(EXC)))
	
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		CFLAGS += -D OSX
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		CFLAGS += -D AMD64 -m64 # Here the extra -m64 flag tells the compiler to compile for 64 bit
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CFLAGS += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		CFLAGS += -D ARM
	endif
endif

LIBFILES := $(call oslibfiles,$(LIBFILES))

# Compiler flags to create dependency makefile (so things can be recompiled if header files are modified)
DEPFLAGS = -MT $@ -MMD -MP -MF $(call ospath,$(DEPDIR)/$*.d)

# Compile command
COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) $(call ospath,$(addprefix -I$(LIBDIR)/,$(INCLUDEDIRS))) -c

# Declare phony targets (targets without a corresponding file)
.PHONY: all run debug release clean

# Run the program every time make is run
all: run

# Use the debug target by default
run: debug
	./$(EXC)

# Apply debug compiler flags & build executable
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(EXC)

# Apply release compiler flags & build executable
release: CFLAGS += $(RELEASEFLAGS)
release: $(EXC)

# Delete all build files
clean:
	$(CLEAN)

# Create all neccessary directories
$(SUBDIRECTORIES):
	$(MKDIR)

$(LIBDIR)/$(call oslibfiles,TerminalGraphics/TerminalGraphics):
	cd $(call ospath,$(LIBDIR)/TerminalGraphics) && $(MAKE)

# The following is from https://make.mad-scientist.net/papers/advanced-auto-dependency-generation

# Link executable
$(EXC): $(SRCS:%.cpp=$(OBJDIR)/%.o) $(addprefix $(LIBDIR)/,$(LIBFILES))
	$(CC) $(CFLAGS) $(call ospath,$^) -o $@

# Compile all object files
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d | $(SUBDIRECTORIES)
	$(COMPILE) -o $(call ospath,$@) $<


# Include all dependency files (so make knows which files to recompile when a header file is updated)
DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))


# CC := g++
# CFLAGS := -g -std=c++11

# EXC := run_coffee_shop

# SRCDIR := src
# OBJDIR := obj
# DEPDIR := $(OBJDIR)/deps
# GRAPHICSDIR := ../AidanTerminalGraphics

# SRCS := $(patsubst $(SRCDIR)/%, %, $(shell find $(SRCDIR) -name '*.cpp'))

# DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# MKDIRS = mkdir -p $(OBJDIR)/$(dir $*) $(DEPDIR)/$(dir $*)
# COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c

# # Make the targets not require a check if the file exists
# .PHONY: all run clean copy

# # Run the program every time we make even if not needing a new compile
# all: run

# run: $(EXC) #copy
# 	./$(EXC)

# copy:
# 	cp -r $(GRAPHICSDIR) $(SRCDIR)

# clean:
# 	rm -rf $(OBJDIR) $(EXC)

# # Partly from https://make.mad-scientist.net/papers/advanced-auto-dependency-generation
# $(EXC): $(SRCS:%.cpp=$(OBJDIR)/%.o)
# 	$(CC) $(CFLAGS) $^ -o $(EXC)

# $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d
# 	$(MKDIRS)
# 	$(COMPILE) $(OUTPUT_OPTION) $<

# DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
# $(DEPFILES):
# include $(wildcard $(DEPFILES))
