#include "src/entity/input_component.h"

#include "SDL2/SDL.h"

#include "src/entity/paddle.h"

void InputComponent::Update(Paddle *paddle, SDL_Event input) {
  if (input.type == SDL_KEYDOWN) {
    switch (input.key.keysym.sym) {
      case SDLK_LEFT:
        paddle->velocity_ = -kPaddleVelocity;
        break;
      case SDLK_RIGHT:
        paddle->velocity_ = kPaddleVelocity;
        break;
      default:
        break;
    }
  } else if (input.type == SDL_KEYUP) {
    paddle->velocity_ = 0;
  }
}
