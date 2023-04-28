#include "src/entity/paddle.h"

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/entity/input_component.h"
#include "src/entity/physics_component.h"
#include "src/graphic/texture.h"

Paddle::Paddle(Texture *texture, SDL_Rect clip)
    : graphics_{ GraphicsComponent(texture, clip) } {}

int Paddle::get_x() {
  return x_;
}

int Paddle::get_velocity() {
  return velocity_;
}

void Paddle::set_x(int x) {
  x_ = x;
}

void Paddle::set_velocity(int velocity) {
  velocity_ = velocity;
}

void Paddle::HandleInput(SDL_Event input) {
  input_.Update(this, input);
}

void Paddle::Update() {
  physics_.Update(this);
  graphics_.Render(x_, y_);
}
