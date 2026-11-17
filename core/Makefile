# Makefile for C programs in Smart Network Routing System

CC = gcc
CFLAGS = -Wall -Wextra -I../include
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Test integration program
test_integration: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/test_integration.c -o $(BUILD_DIR)/test_integration.exe

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

# Build all programs
all: test_integration

.PHONY: clean all
