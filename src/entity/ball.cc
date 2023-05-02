#include "src/entity/ball.h"

#include "SDL2/SDL.h"

#include "src/entity/component/graphics.h"
#include "src/entity/component/physics.h"
#include "src/graphic/texture.h"

Ball::Ball(Texture *texture, SDL_Rect clip)
    : physics_{ PhysicsComponent() },
      graphics_{ GraphicsComponent(texture, clip) } {}

void Ball::Update() {
  physics_.Update(this);
  graphics_.Render(x_, y_);
}
