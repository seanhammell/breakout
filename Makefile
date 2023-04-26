TARGET_EXEC := breakout

# C++ compiler, compiler flags, include directories, and libraries.
CXX := clang++
CXXFLAGS := -g -std=c++17 -pedantic-errors
CXXFLAGS += -Wall -Wextra -Werror
CXXFLAGS += -I.
LDFLAGS := -l SDL2

# Finds all of the .cc files in the specified ./src directories.
SRC_DIR := ./src
SRCS := $(wildcard $(SRC_DIR)/*.cc)
SRCS += $(wildcard $(SRC_DIR)/gfx/*.cc)
SRCS += $(wildcard $(SRC_DIR)/fsm/*.cc)

# Specifies .o files in the ./build directory, maintaining the same file
# structure as the ./src directory.
BUILD_DIR := ./build
OBJS := $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Final build step where the executable is created.
$(BUILD_DIR)/$(TARGET_EXEC) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build step for C++ source files.
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleans up the ./build directory.
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
