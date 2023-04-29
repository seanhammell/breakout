#include "src/entity/paddle.h"

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/entity/input_component.h"
#include "src/entity/physics_component.h"
#include "src/graphic/texture.h"

Paddle::Paddle(Texture *texture, SDL_Rect clip)
    : width_{ texture->get_width() }, height_{ texture->get_height() },
      input_{ InputComponent() }, physics_{ PhysicsComponent() },
      graphics_{ GraphicsComponent(texture, clip) } {}

void Paddle::HandleInput(SDL_Event input) {
  input_.Update(this, input);
}

void Paddle::Update() {
  physics_.Update(this);
  graphics_.Render(x_, y_);
}
