#include "src/entity/paddle.h"

#include "SDL2/SDL.h"

#include "src/entity/component/graphics.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Paddle::Paddle(Texture *texture, SDL_Rect clip)
    : graphics_{ GraphicsComponent(texture, clip) } {}

void Paddle::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN && input.key.repeat == 0) {
    switch (input.key.keysym.sym) {
      case SDLK_LEFT:
        velocity_ -= kPaddleVelocity;
        break;
      case SDLK_RIGHT:
        velocity_ += kPaddleVelocity;
        break;
      default:
        break;
    }
  } else if (input.type == SDL_KEYUP) {
    switch (input.key.keysym.sym) {
      case SDLK_LEFT:
        velocity_ += kPaddleVelocity;
        break;
      case SDLK_RIGHT:
        velocity_ -= kPaddleVelocity;
        break;
      default:
        break;
    }
  }
}

void Paddle::Update() {
  x_ += velocity_;
  if (x_ < 0 || x_ + kPaddleWidth > Renderer::kVirtualWidth) {
    x_ -= velocity_;
  }

  graphics_.Render(x_, y_);
}
