#include "src/entity/paddle.h"

#include "SDL2/SDL.h"

#include "src/entity/component/graphics.h"
#include "src/entity/component/input.h"
#include "src/entity/component/physics.h"
#include "src/graphic/texture.h"

Paddle::Paddle(Texture *texture, SDL_Rect clip)
    : input_{ InputComponent() }, physics_{ PhysicsComponent() },
      graphics_{ GraphicsComponent(texture, clip) } {}

void Paddle::HandleInput(SDL_Event input) {
  input_.Update(this, input);
}

void Paddle::Update() {
  physics_.Update(this);
  graphics_.Render(x_, y_);
}
