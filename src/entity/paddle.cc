#include "src/entity/paddle.h"

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"

Paddle::Paddle(Texture *texture, SDL_Rect clip)
    : graphics_{ GraphicsComponent(texture, clip) } {}

void Paddle::Update() {
  graphics_.Update(x_, y_);
}
