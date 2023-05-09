#include "src/entity/ball.h"

#include <cstdlib>
#include <vector>

#include "SDL2/SDL.h"

#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/entity/physics.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}

void Ball::HandleInput(SDL_Event input) {
  if (input.key.keysym.sym == SDLK_SPACE && x_vel_ == 0 && y_vel_ == 0) {
    x_vel_ = (std::rand() % 7) - 3;
    y_vel_ = -1;
  }
}

void Ball::Update(const Paddle& paddle, std::vector<Brick> *bricks) {
  physics_.Update(this, paddle, bricks);
  if (y_pos_ > Renderer::kVirtualHeight) {
    Reset();
  }
}

void Ball::Render() {
  texture_->Render(x_pos_, y_pos_, &clip_);
}

void Ball::Reset() {
  x_pos_ = (Renderer::kVirtualWidth - Ball::kBallWidth) / 2;
  y_pos_ = Paddle::kPaddleYPos - kBallHeight;
  x_vel_ = 0;
  y_vel_ = 0;
}
