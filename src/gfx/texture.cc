#include "src/gfx/texture.h"

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "src/gfx/font.h"

// Loads a texture from the provided image path and returns whether the load was
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

// Loads a texture from provided font and text and returns whether the load was
// successful.
bool Texture::LoadFromText(SDL_Renderer *renderer, const Font& font,
                           const char *text) {
  Free();

  SDL_Surface *text_surface = TTF_RenderText_Solid(font.GetFont(), text,
                                                   font.GetColor());
  if (text_surface == NULL) {
    fprintf(stderr, "Error rendering text surface: %s\n", TTF_GetError());
    return false;
  }

  texture_ = SDL_CreateTextureFromSurface(renderer, text_surface);
  if (texture_ == NULL) {
    fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
    return false;
  }

  width_ = text_surface->w;
  height_ = text_surface->h;

  return texture_ != NULL;
}

void Texture::Render(SDL_Renderer *renderer, const int x, const int y) {
  SDL_Rect dest{ x, y, width_, height_ };
  SDL_RenderCopy(renderer, texture_, NULL, &dest);
}

// Frees the current texture if it exists.
void Texture::Free() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
  }
}
