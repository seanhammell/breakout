#include "src/entity/ball.h"

#include <cstdlib>

#include "SDL2/SDL.h"

#include "src/entity/brick.h"
#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}

void Ball::HandleInput(SDL_Event input) {
  if (input.key.keysym.sym == SDLK_SPACE) {
    x_vel_ = 1;
    y_vel_ = 1;
  }
}

void Ball::Update() {

}

void Ball::Render() {
  texture_->Render(x_pos_, y_pos_, &clip_);
}
