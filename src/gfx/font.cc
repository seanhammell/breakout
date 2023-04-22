#include "src/gfx/font.h"

#include <stdio.h>

#include <SDL2/SDL_ttf.h>

// Loads a font from the given file and returns whether the load was successful.
bool Font::LoadFromFile(const char *path, const int size) {
  Free();

  font_ = TTF_OpenFont(path, size);
  if (font_ == NULL) {
    fprintf(stderr, "Error opening font: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

// Frees the current font if it exists.
void Font::Free() {
  if (font_ != NULL) {
    TTF_CloseFont(font_);
    font_ = NULL;
  }
}
