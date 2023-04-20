CC = clang++
CFLAGS = -g -std=c++17 -pedantic-errors -Wall -Wextra -Werror
SRC = src/main.cc src/renderer.cc src/texture.cc
INC = -I .
LIB = -l SDL2 -l SDL2_image
TARGET = breakout

all:
	$(CC) $(CFLAGS) $(INC) $(LIB) $(SRC) -o $(TARGET)