# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files (dynamically detected)
SRCS = $(wildcard src/*.c)

# Binary files (derived from sources)
BINS = $(patsubst src/%.c, bin/%,$(SRCS))

# Default target: build all binaries
.PHONY: all
all: $(BINS)

# Rule to create bin/ directory if not exists
$(BINS): | bin
bin:
	mkdir -p bin

# Rule to compile each source file to its binary
bin/%: src/%.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove binaries
.PHONY: clean
clean:
	rm -f $(BINS)
