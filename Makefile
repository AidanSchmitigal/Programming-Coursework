CC := g++
CFLAGS := -g -std=c++11

EXC := Escape162

SRCDIR := src
OBJDIR := obj
DEPDIR := $(OBJDIR)/deps
LIBDIR := lib

SRCS := $(patsubst $(SRCDIR)/%, %, $(shell find $(SRCDIR) -name '*.cpp'))
LIBS := TerminalGraphics

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

MKDIRS = mkdir -p $(OBJDIR)/$(dir $*) $(DEPDIR)/$(dir $*)
COMPILE = $(CC) $(DEPFLAGS) $(CFLAGS) -c

# Make the targets not require a check if the file exists
.PHONY: all run clean upload

# Run the program every time we make even if not needing a new compile
all: copy run upload

run: $(EXC) #copy
	./$(EXC)

clean:
	rm -rf $(OBJDIR) $(EXC)

copy:
	cp -r $(LIBDIR)/LIBS $(SRCDIR)

upload:
	@if [ "$(USER)" = "aidan" ]; then \
		echo "\033[0;36m"; \
		scp -i ~/.ssh/rsa_flip -r * schmitia@flip.engr.oregonstate.edu:"~/assignments/$(EXC)"; \
		echo "\033[0;32m"; \
		ssh -i ~/.ssh/rsa_flip schmitia@flip.engr.oregonstate.edu "cd ~/assignments/$(EXC); make"; \
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