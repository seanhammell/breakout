#include "src/media/texture.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "src/game.h"

Texture::~Texture() { Free(); }

bool Texture::LoadFromFile(const char *path) {
  Free();

  SDL_Surface *sprite_sheet{IMG_Load(path)};
  if (sprite_sheet == NULL) {
    fprintf(stderr, "Error loading image: %s\n", IMG_GetError());
    return false;
  }

  SDL_Texture *temp{SDL_CreateTextureFromSurface(kGame.renderer.get_renderer(),
                                                 sprite_sheet)};
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

bool Texture::LoadFromText(const Font &font, const char *text) {
  Free();

  SDL_Surface *surface{TTF_RenderText_Solid_Wrapped(
      font.get_font(), text, font.get_color(), Renderer::kVirtualWidth)};
  if (surface == NULL) {
    fprintf(stderr, "Error rendering text surface: %s\n", TTF_GetError());
    return false;
  }

  texture_ =
      SDL_CreateTextureFromSurface(kGame.renderer.get_renderer(), surface);
  if (texture_ == NULL) {
    fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
    return false;
  }

  width_ = surface->w;
  height_ = surface->h;

  return texture_ != NULL;
}

void Texture::Render(const int x, const int y, SDL_Rect *clip) {
  SDL_Rect dest{x, y, width_, height_};
  if (clip != NULL) {
    dest.w = clip->w;
    dest.h = clip->h;
  }
  SDL_RenderCopy(kGame.renderer.get_renderer(), texture_, clip, &dest);
}

void Texture::Free() {
  if (texture_ != NULL) {
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
  }
}
