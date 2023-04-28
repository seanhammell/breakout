#ifndef SRC_ENTITY_PHYSICS_COMPONENT_H_
#define SRC_ENTITY_PHYSICS_COMPONENT_H_

class Paddle;

class PhysicsComponent {
 public:
  PhysicsComponent() = default;

  ~PhysicsComponent() = default;

  void Update(Paddle *paddle);

 private:
  bool OutsideScreenBounds(Paddle *paddle);
};

#endif  // SRC_ENTITY_PHYSICS_COMPONENT_H_
