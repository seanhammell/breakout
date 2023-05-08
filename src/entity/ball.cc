#include "src/entity/ball.h"

#include <cmath>
#include <cstdlib>

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
    x_vel_ = 1;
    y_vel_ = -3;
  }
}

void Ball::Update(const Paddle& paddle) {
  physics_.Update(this, paddle);
}

void Ball::Render() {
  texture_->Render(x_pos_, y_pos_, &clip_);
}
