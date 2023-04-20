#include "src/texture.h"

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Frees the current texture if it exists.
void Texture::Free() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
  }
}

// Loads a texture from the given file and returns whether the load was
// successful.
bool Texture::LoadFromFile(SDL_Renderer *renderer, const char *path) {
  Free();

  SDL_Surface *sprite_sheet{ IMG_Load(path) };
  if (sprite_sheet == NULL) {
    fprintf(stderr, "Error loading image: %s\n", IMG_GetError());
    return false;
  }

  SDL_Texture *temp{ SDL_CreateTextureFromSurface(renderer, sprite_sheet) };
  if (temp == NULL) {
    fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
    SDL_FreeSurface(sprite_sheet);
    return false;
  }

  texture_ = temp;
  width_ = sprite_sheet->w;
  height_ = sprite_sheet->h;
  SDL_FreeSurface(sprite_sheet);

  return texture_ != NULL;
}

void Texture::Render(SDL_Renderer *renderer, const int x, const int y) {
  SDL_Rect dest{ x, y, width_, height_ };
  SDL_RenderCopy(renderer, texture_, NULL, &dest);
}
