#include "src/entity/brick.h"

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

Brick::Brick(int x, int y, BrickType type, Texture *texture)
    : x_pos_{ x }, y_pos_{ y }, //type_{ type },
      texture_{ texture },
      clip_{ type * kClipWidth - 8, 0, kClipWidth, kClipHeight } {}

void Brick::Render() {
  texture_->Render(x_pos_, y_pos_, &clip_);
}
