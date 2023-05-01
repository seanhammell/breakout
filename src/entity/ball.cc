#include "src/entity/ball.h"

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/entity/physics_component.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : physics_{ PhysicsComponent() },
      graphics_{ GraphicsComponent(texture, clip) } {}

void Ball::Update() {
  physics_.Update(this);
  graphics_.Render(x_, y_);
}
