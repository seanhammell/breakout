#ifndef SRC_ENTITY_BRICK_H_
#define SRC_ENTITY_BRICK_H_

#include <array>

#include "SDL2/SDL.h"
#include "src/media/texture.h"

class Brick {
 public:
  enum BrickType {
    kNoType,
    kYellow,
    kGreen,
    kOrange,
    kRed,
    kTotalTypes,
  };

  static const int kClipWidth{8};
  static const int kClipHeight{3};

  static const int kBrickWidth{9};
  static const int kBrickHeight{4};

  static constexpr size_t kMaxBricks{176};

  Brick() = default;
  Brick(int x, int y, BrickType type, Texture *texture);

  // Easy conversion from BrickType to int.
  constexpr int operator+(BrickType type);

  ~Brick() = default;

  // Loads a set of bricks from the given file into a vector.
  static bool Load(std::array<Brick, kMaxBricks> *bricks, const char *file);

  int get_x_pos() const { return x_pos_; }
  int get_y_pos() const { return y_pos_; }
  bool is_hit() const { return hit_; }
  BrickType get_type() const { return type_; }
  int value() const { return type_ * 2 - 1; }

  void set_x_pos(int x_pos) { x_pos_ = x_pos; }
  void set_y_pos(int y_pos) { y_pos_ = y_pos; }
  void set_type(int type);
  void hit() { hit_ = true; }

  // Renders the Brick to the screen.
  void Render();

 private:
  int x_pos_{0};
  int y_pos_{0};
  bool hit_{false};
  BrickType type_{kNoType};
  Texture *texture_{NULL};
  SDL_Rect clip_{};
};

#endif  // SRC_ENTITY_BRICK_H_
