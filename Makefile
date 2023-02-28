CC := g++
CFLAGS := -g -std=c++11

EXC := Escape162.runme

SRCDIR := src
OBJDIR := obj
DEPDIR := $(OBJDIR)/deps

SRCS := $(patsubst $(SRCDIR)/%, %, $(shell find $(SRCDIR) -name '*.cpp'))

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

MKDIRS = @mkdir -p $(OBJDIR)/$(dir $*) $(DEPDIR)/$(dir $*)
COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c

# Make the targets not require a check if the file exists
.PHONY: all run clean upload copy

# Run the program every time we make even if not needing a new compile
all: copy run upload

run: copy $(EXC)
	./$(EXC)

clean:
	rm -rf $(OBJDIR) $(EXC)

copy:
	@if [ "$(USER)" = "aidan" ]; then \
		git submodule update --remote; \
		echo "\033[0;33m"; \
		cd libs/TerminalGraphics; make split; \
		echo "\033[0m"; \
		cd ../../; \
		cp -r libs/TerminalGraphics/split/ $(SRCDIR)/graphics/; \
	fi

upload:
	@if [ "$(USER)" = "aidan" ]; then \
		echo "\033[0;36m"; \
		scp -i ~/.ssh/rsa_flip -r src Makefile schmitia@flip.engr.oregonstate.edu:"~/assignments/$(EXC)"; \
		echo "\033[0;32m"; \
		ssh -i ~/.ssh/rsa_flip schmitia@flip.engr.oregonstate.edu "cd ~/assignments/$(EXC); make clean; make; valgrind $(EXC); cd ../; rm -rf $(EXC);"; \
		echo "\033[0m"; \
	fi

# Partly from https://make.mad-scientist.net/papers/advanced-auto-dependency-generation
$(EXC): $(SRCS:%.cpp=$(OBJDIR)/%.o)
	$(CC) $(CFLAGS) $^ -o $(EXC)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	$(MKDIRS)
	$(COMPILE) $(OUTPUT_OPTION) $<

DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):
include $(wildcard $(DEPFILES))