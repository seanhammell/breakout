#include "src/entity/ball.h"

#include <array>
#include <cstdlib>

#include "SDL2/SDL.h"
#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/entity/physics.h"
#include "src/graphic/renderer.h"
#include "src/media/texture.h"

Ball::Ball(Texture* texture, SDL_Rect clip) : texture_{texture}, clip_{clip} {}

void Ball::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    if (input.key.keysym.sym == SDLK_SPACE && !live_) {
      x_vel_ = (std::rand() % 2) == 0 ? -1 : 1;
      y_vel_ = -y_vel_;
      live_ = true;
    }
  }
}

void Ball::Update(const Paddle& paddle,
                  std::array<Brick, Brick::kMaxBricks>* bricks) {
  if (live_) {
    physics_.Update(this, paddle, bricks);
    if (y_pos_ > Renderer::kVirtualHeight) {
      y_pos_ = Paddle::kPaddleYPos - kBallHeight;
      CenterOnPaddle(paddle);
      live_ = false;
      --n_lives_;
    }
  } else {
    CenterOnPaddle(paddle);
  }
}

void Ball::Render() { texture_->Render(x_pos_, y_pos_, &clip_); }

void Ball::CenterOnPaddle(const Paddle& paddle) {
  x_pos_ = paddle.get_x_pos() + (Paddle::kPaddleWidth - kBallWidth) / 2;
}
