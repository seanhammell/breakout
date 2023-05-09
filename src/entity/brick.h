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

  static const int kClipWidth{ 8 };
  static const int kClipHeight{ 3 };

  static const int kBrickWidth{ 9 };
  static const int kBrickHeight{ 4 };

  Brick() = default;
  Brick(int x, int y, BrickType type, Texture *texture);

  ~Brick() = default;

  int get_x_pos() const { return x_pos_; }
  int get_y_pos() const { return y_pos_; }
  bool is_hit() const { return hit_; }

  void hit() { hit_ = true; }

  // Renders the Brick to the screen.
  void Render();

 private:
  int x_pos_{ 0 };
  int y_pos_{ 0 };
  bool hit_{ false };
  //BrickType type_{ };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_BRICK_H_
