#include "src/entity/ball.h"

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : texture_{ texture }, clip_{ clip } {}

void Ball::Update() {
  texture_->Render(x_, y_, &clip_);
}
