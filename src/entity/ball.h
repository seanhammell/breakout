#ifndef SRC_ENTITY_BALL_H_
#define SRC_ENTITY_BALL_H_

#include "SDL2/SDL.h"

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

  // Serves the Ball if it isn't live.
  void HandleInput(SDL_Event input);

  // Updates the Ball with one frame of behavior.
  void Update();

  // Renders the Ball to the screen.
  void Render();

 private:
  int x_pos_{ (Renderer::kVirtualWidth - Ball::kBallWidth) / 2 };
  int y_pos_{ Paddle::kPaddleY - kBallHeight };
  int x_vel_{ };
  int y_vel_{ };
  Texture *texture_{ NULL };
  SDL_Rect clip_{ };
};

#endif  // SRC_ENTITY_BALL_H_
