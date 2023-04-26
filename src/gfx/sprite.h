#ifndef SRC_GFX_SPRITE_H_
#define SRC_GFX_SPRITE_H_

#include "SDL2/SDL.h"

// Represents an individual sprite as part of a larger sprite sheet.
struct Sprite {
  SDL_Rect clip;
  int x;
  int y;
};

#endif  // SRC_GFX_SPRITE_H_
