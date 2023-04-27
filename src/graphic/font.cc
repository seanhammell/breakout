#include "src/graphic/font.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

Font::~Font() {
  Free();
}

TTF_Font *Font::font() const {
  return font_;
}

SDL_Color Font::color() const {
  return color_;
}

void Font::Free() {
  if (font_ != NULL) {
    TTF_CloseFont(font_);
    font_ = NULL;
  }
}
