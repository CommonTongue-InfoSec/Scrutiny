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

# Run targets
.PHONY: run_baseliner
run_baseliner: bin/baseliner
	./bin/baseliner

.PHONY: run_targetProc0
run_targetProc0: bin/targetProc0
	./bin/targetProc0

.PHONY: run_targetProc1
run_targetProc1: bin/targetProc1
	./bin/targetProc1

.PHONY: run_targetProc2
run_targetProc2: bin/targetProc2
	./bin/targetProc2

.PHONY: run_monitor
run_monitor: bin/monitor
	./bin/monitor