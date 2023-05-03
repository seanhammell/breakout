#include "src/entity/ball.h"

#include "SDL2/SDL.h"

#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}

void Ball::Update() {
  if (is_live_) {
    x_ += x_velocity_;
    y_ += y_velocity_;

    if (x_ < 0 || x_ + kBallWidth > Renderer::kVirtualWidth) {
      x_ -= x_velocity_;
      x_velocity_ = -x_velocity_;
    }

    if (y_ < 0 || y_ + kBallHeight > Renderer::kVirtualHeight) {
      y_ -= y_velocity_;
      y_velocity_ = -y_velocity_;
    }
  }

  texture_->Render(x_, y_, &clip_);
}
