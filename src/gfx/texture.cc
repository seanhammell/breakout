#include "src/gfx/texture.h"

#include "SDL2/SDL.h"

void Texture::Free() {
  if (texture_ != NULL) {
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
  }
}
