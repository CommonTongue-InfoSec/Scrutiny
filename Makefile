# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -I$(SRC_DIR)
LDFLAGS =

# Dirs
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
BASLINER_SRCS = $(SRC_DIR)/baseliner.c $(SRC_DIR)/syscalls.c $(SRC_DIR)/utils.c
TARGET0_SRCS = $(SRC_DIR)/targetProc0.c
TARGET1_SRCS = $(SRC_DIR)/targetProc1.c
TARGET2_SRCS = $(SRC_DIR)/targetProc2.c

# Objs
BASLINER_OBJS = $(BASLINER_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET0_OBJS = $(TARGET0_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET1_OBJS = $(TARGET1_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET2_OBJS = $(TARGET2_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executables
BASLINER_EXEC = $(BIN_DIR)/baseliner
TARGET0_EXEC = $(BIN_DIR)/targetProc0
TARGET1_EXEC = $(BIN_DIR)/targetProc1
TARGET2_EXEC = $(BIN_DIR)/targetProc2

# All targets
EXECUTABLES = $(BASLINER_EXEC) $(TARGET0_EXEC) $(TARGET1_EXEC) $(TARGET2_EXEC)

# Default target
all: $(EXECUTABLES)

# Link executables
$(BASLINER_EXEC): $(BASLINER_OBJS) | $(BIN_DIR)
	$(CC) $(BASLINER_OBJS) $(LDFLAGS) -o $@

$(TARGET0_EXEC): $(TARGET0_OBJS) | $(BIN_DIR)
	$(CC) $(TARGET0_OBJS) $(LDFLAGS) -o $@

$(TARGET1_EXEC): $(TARGET1_OBJS) | $(BIN_DIR)
	$(CC) $(TARGET1_OBJS) $(LDFLAGS) -o $@

$(TARGET2_EXEC): $(TARGET2_OBJS) | $(BIN_DIR)
	$(CC) $(TARGET2_OBJS) $(LDFLAGS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -M -MT $@ $< > $(@:.o=.d)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# make run <target>
run: $(EXECUTABLES)
	@if [ -z "$(filter baseliner targetProc0 targetProc1 targetProc2,$(word 2,$(MAKECMDGOALS)))" ]; then \
    	echo "Error: Please specify a valid target to run (baseliner, targetProc0, targetProc1, targetProc2)"; \
    	echo "Example: make run baseliner"; \
    	exit 1; \
	fi
	@echo "Running $(BIN_DIR)/$(word 2,$(MAKECMDGOALS))..."
	@$(BIN_DIR)/$(word 2,$(MAKECMDGOALS))

# no running as file
%:
	@:

clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/*

# Include dependencies
-include $(OBJ_DIR)/*.d

.PHONY: all clean run