#include "src/entity/paddle.h"

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/entity/input_component.h"
#include "src/graphic/texture.h"

Paddle::Paddle(Texture *texture, SDL_Rect clip)
    : graphics_{ GraphicsComponent(texture, clip) } {}

void Paddle::set_velocity(int velocity) {
  velocity_ = velocity;
}

void Paddle::HandleInput(SDL_Event input) {
  input_.Update(this, input);
}

void Paddle::Update() {
  x_ += velocity_;
  graphics_.Render(x_, y_);
}