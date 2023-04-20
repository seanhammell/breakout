CC = clang++
CFLAGS = -g -std=c++17 -pedantic-errors -Wall -Wextra -Werror
SRC = src/main.cc
INC = -I .
LIB = -l SDL2
TARGET = breakout

all:
	$(CC) $(CFLAGS) $(INC) $(LIB) $(SRC) -o $(TARGET)