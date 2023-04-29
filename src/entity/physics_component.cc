#include "src/entity/physics_component.h"

#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"

void PhysicsComponent::Update(Paddle *paddle) {
  paddle->x_ += paddle->velocity_;
  if (OutsideScreenBounds(paddle)) {
    paddle->x_ -= paddle->velocity_;
  }
}

bool PhysicsComponent::OutsideScreenBounds(Paddle *paddle) {
  return (paddle->x_ < 0 ||
          paddle->x_ + paddle->width_ > Renderer::kVirtualWidth);
}
