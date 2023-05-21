#include "src/media/font.h"

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

Font::~Font() {
  Free();
}

bool Font::LoadFromFile(const char *path, const int size) {
  Free();

  font_ = TTF_OpenFont(path, size);
  if (font_ == NULL) {
    fprintf(stderr, "Error opening font: %s\n", TTF_GetError());
    return false;
  }
  size_ = size;

  return true;
}

void Font::Free() {
  if (font_ != NULL) {
    TTF_CloseFont(font_);
    font_ = NULL;
  }
}
