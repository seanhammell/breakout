#include "src/entity/input_component.h"

#include "SDL2/SDL.h"

#include "src/entity/paddle.h"

void InputComponent::Update(Paddle *paddle, SDL_Event input) {
  switch (input.key.keysym.sym) {
    case SDLK_LEFT:
      paddle->set_velocity(-kPaddleVelocity);
      break;
    case SDLK_RIGHT:
      paddle->set_velocity(kPaddleVelocity);
      break;
    default:
      paddle->set_velocity(0);
      break;
  }
}
