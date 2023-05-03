#ifndef SRC_ENTITY_BALL_H_
#define SRC_ENTITY_BALL_H_

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Ball {
 public:
  static const int kBallWidth{ 2 };
  static const int kBallHeight{ 2 };

  Ball() = default;
  Ball(Texture *texture, SDL_Rect clip = {16, 3, kBallWidth, kBallHeight});

  ~Ball() = default;

  int get_x() { return x_; }
  int get_y() { return y_; }
  int get_y_velocity() { return y_velocity_; }

  void set_x_velocity(int velocity) { x_velocity_ = velocity; }
  void set_y_velocity(int velocity) { y_velocity_ = velocity; }

  // Updates the Ball with one frame of behavior.
  void Update();

 private:
  int x_{ (Renderer::kVirtualWidth - kBallWidth) / 2 };
  int y_{ Renderer::kVirtualHeight - 24};
  int x_velocity_{ 0 };
  int y_velocity_{ 1 };
  bool is_live_{ true };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_BALL_H_
