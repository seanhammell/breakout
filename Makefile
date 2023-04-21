CC = clang++
CFLAGS = -g -std=c++17 -pedantic-errors -Wall -Wextra -Werror
SRC = src/main.cc src/renderer.cc src/texture.cc src/font.cc
INC = -I .
LIB = -l SDL2 -l SDL2_image -l SDL2_ttf
TARGET = breakout

all:
	$(CC) $(CFLAGS) $(INC) $(LIB) $(SRC) -o $(TARGET)