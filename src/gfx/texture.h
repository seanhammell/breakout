#ifndef SRC_GFX_TEXTURE_H_
#define SRC_GFX_TEXTURE_H_

#include "SDL2/SDL.h"

class Texture {
 public:
  Texture() {}
  ~Texture() { Free(); }

 private:
  // Frees the current Texture if it exists.
  void Free();

  SDL_Texture *texture_{ NULL };
  int width_{ 0 };
  int height_{ 0 };
};

#endif  // SRC_GFX_TEXTURE_H_
