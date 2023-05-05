#ifndef SRC_ENTITY_BALL_H_
#define SRC_ENTITY_BALL_H_

#include <cstdlib>
#include <vector>

#include "SDL2/SDL.h"

#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Ball {
 public:
  static const int kBallWidth{ 2 };
  static const int kBallHeight{ 2 };

  Ball() = default;
  Ball(Texture *texture, SDL_Rect clip = {24, 3, kBallWidth, kBallHeight});

  ~Ball() = default;

  int get_x() const { return x_; }
  int get_y() const { return y_; }
  int get_x_velocity() const { return x_velocity_; }
  int get_y_velocity() const { return y_velocity_; }

  void set_x_velocity(int velocity) { x_velocity_ = velocity; }
  void set_y_velocity(int velocity) { y_velocity_ = velocity; }

  // Serves the Ball if it isn't live.
  void HandleInput(SDL_Event input);

  // Updates the Ball with one frame of behavior.
  void Update(const Paddle& paddle, std::vector<Brick> *bricks);

  // Renders the Ball to the screen.
  void Render();

 private:
  // Applies the Ball's velocity.
  void Move();
  void Unmove();

  // Handles collisions with the Paddle and Bricks.
  void PaddleCollision(const Paddle& paddle);
  void BrickCollision(std::vector<Brick> *bricks);

  int x_{ (Renderer::kVirtualWidth - kBallWidth) / 2 };
  int y_{ Renderer::kVirtualHeight - 23};
  int x_velocity_{ (std::rand() % 7) - 3 };
  int y_velocity_{ -1 };
  bool is_live_{ true };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_BALL_H_
