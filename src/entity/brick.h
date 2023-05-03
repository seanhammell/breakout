#ifndef SRC_ENTITY_BRICK_H_
#define SRC_ENTITY_BRICK_H_

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

class Brick {
 public:
  enum BrickType {
    kYellow,
    kGreen,
    kOrange,
    kRed,
  };

  static const int kBrickWidth{ 7 };
  static const int kBrickHeight{ 3 };

  Brick() = default;
  Brick(int x, int y, BrickType type, Texture *texture);

  ~Brick() = default;

  // Renders the Brick to the screen.
  void Render();

 private:
  int x_{ 0 };
  int y_{ 0 };
  //BrickType type_{ };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_BRICK_H_
