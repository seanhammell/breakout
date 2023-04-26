#ifndef SRC_GFX_TEXTURE_H_
#define SRC_GFX_TEXTURE_H_

#include "SDL2/SDL.h"

class Texture {
 public:
  Texture() {}
  ~Texture() { Free(); }

  // Loads a texture from the given path.
  bool LoadFromFile(const char *path);

 private:
  // Frees the current texture if it exists.
  void Free();

  SDL_Texture *texture_{ NULL };
  int width_{ 0 };
  int height_{ 0 };
};

#endif  // SRC_GFX_TEXTURE_H_
