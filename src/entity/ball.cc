#include "src/entity/ball.h"

#include <cstdlib>

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}

void Ball::HandleInput(SDL_Event input) {
  if (!is_live_ && input.type == SDL_KEYDOWN) {
    if (input.key.keysym.sym == SDLK_SPACE) {
      is_live_ = true;
    }
  }
}

void Ball::Update() {
  if (is_live_) {
    x_ += x_velocity_;
    y_ += y_velocity_;

    if (x_ < 0 || x_ + kBallWidth > Renderer::kVirtualWidth) {
      x_ -= x_velocity_;
      x_velocity_ = -x_velocity_;
    }

    if (y_ < 0) {
      y_ -= y_velocity_;
      y_velocity_ = -y_velocity_;
    }

    if (y_ > Renderer::kVirtualHeight) {
      x_ = (Renderer::kVirtualWidth - kBallWidth) / 2;
      y_ = Renderer::kVirtualHeight - 23;
      x_velocity_ = (std::rand() % 8) - 4;
      y_velocity_ = -1;
      is_live_ = false;
    }
  }
}

void Ball::Render() {
  texture_->Render(x_, y_, &clip_);
}
