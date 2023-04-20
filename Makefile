CC = clang++
CFLAGS = -g -std=c++17 -pedantic-errors -Wall -Wextra -Werror
SRC = src/main.cc
TARGET = breakout

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)