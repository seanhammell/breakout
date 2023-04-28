#include "src/entity/physics_component.h"

#include "src/entity/paddle.h"
#include "src/graphic/renderer.h"

void PhysicsComponent::Update(Paddle *paddle) {
  paddle->set_x(paddle->get_x() + paddle->get_velocity());
  if (OutsideScreenBounds(paddle)) {
    paddle->set_x(paddle->get_x() - paddle->get_velocity());
  }
}

bool PhysicsComponent::OutsideScreenBounds(Paddle *paddle) {
  return (paddle->get_x() < 0 ||
          paddle->get_x() + Paddle::kWidth > Renderer::kVirtualWidth);
}
