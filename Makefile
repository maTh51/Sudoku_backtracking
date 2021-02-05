CC := g++
SRCDIR := src
OBJDIR := build
BINDIR := bin
MAIN := main.cpp
SRCEXT := cpp

SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
$(info SOURCES = $(SOURCES))

OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
$(info OBJECTS = $(OBJECTS))

CFLAGS := -std=c++11
INC := -I include/

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: clean main

clean:
	$(RM) -rf $(BINDIR) $(OBJDIR) *.gcda *.gcno main main.dSYM

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(INC) $^ -o tp3
