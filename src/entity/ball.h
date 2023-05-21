#ifndef SRC_ENTITY_BALL_H_
#define SRC_ENTITY_BALL_H_

#include <array>
#include <cstdlib>

#include "SDL2/SDL.h"

#include "src/entity/paddle.h"
#include "src/entity/physics.h"
#include "src/graphic/renderer.h"
#include "src/media/texture.h"

class Ball {
 public:
  static const int kBallWidth{ 2 };
  static const int kBallHeight{ 2 };

  Ball() = default;
  Ball(Texture *texture, SDL_Rect clip = {24, 3, kBallWidth, kBallHeight});

  ~Ball() = default;

  int remaining_lives() { return n_lives_; }

  // Serves the Ball if it isn't live.
  void HandleInput(SDL_Event input);

  // Updates the Ball with one frame of behavior.
  void Update(const Paddle& paddle,
              std::array<Brick, Brick::kMaxBricks> *bricks);

  // Renders the Ball to the screen.
  void Render();

 private:
  friend class Physics;

  // Centers the Ball on the Paddle.
  void CenterOnPaddle(const Paddle& paddle);

  int x_pos_{ (Renderer::kVirtualWidth - Ball::kBallWidth) / 2 };
  int y_pos_{ Paddle::kPaddleYPos - kBallHeight };
  int x_vel_{ (std::rand() % 7) - 3 };
  int y_vel_{ -1 };
  bool live_{ true };
  int n_lives_{ 3 };
  Physics physics_{ };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_BALL_H_
