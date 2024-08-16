#include "src/entity/paddle.h"

#include "SDL2/SDL.h"
#include "src/graphic/renderer.h"
#include "src/media/texture.h"

Paddle::Paddle(Texture *texture, SDL_Rect clip)
    : texture_{texture}, clip_{clip} {}

void Paddle::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_LEFT:
        x_vel_ -= kPaddleVelocity;
        break;
      case SDLK_RIGHT:
        x_vel_ += kPaddleVelocity;
        break;
      default:
        break;
    }
  } else if (input.type == SDL_KEYUP) {
    switch (input.key.keysym.sym) {
      case SDLK_LEFT:
        x_vel_ += kPaddleVelocity;
        break;
      case SDLK_RIGHT:
        x_vel_ -= kPaddleVelocity;
        break;
      default:
        break;
    }
  }
}

void Paddle::Update() {
  x_pos_ += x_vel_;
  if (x_pos_ < 0) {
    x_pos_ = 0;
  } else if (x_pos_ + kPaddleWidth > Renderer::kVirtualWidth) {
    x_pos_ = Renderer::kVirtualWidth - kPaddleWidth;
  }
}

void Paddle::Render() { texture_->Render(x_pos_, kPaddleYPos, &clip_); }
