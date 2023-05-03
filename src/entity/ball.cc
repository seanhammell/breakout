#include "src/entity/ball.h"

#include "SDL2/SDL.h"

#include "src/entity/component/graphics.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : graphics_{ GraphicsComponent(texture, clip) } {}

void Ball::Update() {
  graphics_.Render(x_, y_);
}
