#include "src/entity/brick.h"

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

Brick::Brick(int x, int y, BrickType type, Texture *texture)
    : x_{ x }, y_{ y }, //type_{ type },
      texture_{ texture },
      clip_{ type * kBrickWidth, 0, kBrickWidth, kBrickHeight } {}

void Brick::Render() {
  texture_->Render(x_, y_, &clip_);
}