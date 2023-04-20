#ifndef SRC_TEXTURE_H_
#define SRC_TEXTURE_H_

#include <SDL2/SDL.h>

class Texture {
 public:
  Texture() {}
  ~Texture() { Destroy(); }

 private:
  void Destroy();

  SDL_Texture *texture_{ nullptr };
  int width_{ 0 };
  int height_{ 0 };
};

#endif  // SRC_TEXTURE_H_
