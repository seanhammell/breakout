#include "src/gfx/texture.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "src/state.h"

bool Texture::LoadFromFile(const char *path) {
  Free();

  SDL_Surface *sprite_sheet{ IMG_Load(path) };
  if (sprite_sheet == NULL) {
    fprintf(stderr, "Error loading image: %s\n", IMG_GetError());
    return false;
  }

  SDL_Texture *temp{ SDL_CreateTextureFromSurface(kState.renderer.GetRenderer(),
                                                  sprite_sheet) };
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

void Texture::Free() {
  if (texture_ != NULL) {
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
  }
}
