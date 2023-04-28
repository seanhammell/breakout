#include "src/graphic/font.h"

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

Font::~Font() {
  Free();
}

TTF_Font *Font::get_font() const {
  return font_;
}

SDL_Color Font::get_color() const {
  return color_;
}

bool Font::LoadFromFile(const char *path, const int size) {
  Free();

  font_ = TTF_OpenFont(path, size);
  if (font_ == NULL) {
    fprintf(stderr, "Error opening font: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

void Font::Free() {
  if (font_ != NULL) {
    TTF_CloseFont(font_);
    font_ = NULL;
  }
}
