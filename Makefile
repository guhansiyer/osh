# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Directories
SRC_DIR = src
BUILD_DIR = build
BUILTIN_DIR = $(SRC_DIR)/builtin
EXEC_DIR = $(SRC_DIR)/exec
INPUT_DIR = $(SRC_DIR)/input
PARSE_DIR = $(SRC_DIR)/parse
UTIL_DIR = $(SRC_DIR)/util

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(BUILTIN_DIR)/builtin.c \
       $(EXEC_DIR)/exec.c \
       $(INPUT_DIR)/read_input.c \
       $(PARSE_DIR)/parsing.c

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Include directories
INCLUDES = -I$(BUILTIN_DIR) -I$(EXEC_DIR) -I$(INPUT_DIR) -I$(PARSE_DIR) -I$(UTIL_DIR)

# Output executable
TARGET = osh

# Build rules
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rules
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
