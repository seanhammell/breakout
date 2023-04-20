#include "src/texture.h"

#include <SDL2/SDL.h>

// Destroys the current texture if it exists.
void Texture::Destroy() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
  }
}
