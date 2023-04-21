#ifndef SRC_TEXTURE_H_
#define SRC_TEXTURE_H_

#include <SDL2/SDL.h>

#include "src/font.h"

class Texture {
 public:
  Texture() {}
  ~Texture() { Free(); }

  bool LoadFromFile(SDL_Renderer *renderer, const char *path);
  bool LoadFromText(SDL_Renderer *renderer, const Font& font, const char *text);

  void Render(SDL_Renderer *render, const int x, const int y);

 private:
  void Free();

  SDL_Texture *texture_{ nullptr };
  int width_{ 0 };
  int height_{ 0 };
};

#endif  // SRC_TEXTURE_H_
