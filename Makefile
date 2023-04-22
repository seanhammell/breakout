CC = clang++
CFLAGS = -g -std=c++17 -pedantic-errors -Wall -Wextra -Werror
SRC = src/main.cc src/gfx/renderer.cc src/gfx/texture.cc src/gfx/font.cc src/gfx/frame_rate.cc
INC = -I .
LIB = -l SDL2 -l SDL2_image -l SDL2_ttf
TARGET = breakout

all:
	$(CC) $(CFLAGS) $(INC) $(LIB) $(SRC) -o $(TARGET)