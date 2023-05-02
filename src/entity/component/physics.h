#ifndef SRC_ENTITY_COMPONENT_PHYSICS_H_
#define SRC_ENTITY_COMPONENT_PHYSICS_H_

class Ball;
class Paddle;

class PhysicsComponent {
 public:
  PhysicsComponent() = default;

  ~PhysicsComponent() = default;

  void Update(Ball *) {}
  void Update(Paddle *paddle);

 private:
  bool OutsideScreenBounds(Paddle *paddle);
};

#endif  // SRC_ENTITY_COMPONENT_PHYSICS_H_
