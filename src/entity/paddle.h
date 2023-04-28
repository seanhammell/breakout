#ifndef SRC_ENTITY_PADDLE_H_
#define SRC_ENTITY_PADDLE_H_

#include "src/graphic/renderer.h"

class Paddle {
 public:
  Paddle() {}
  ~Paddle() {}

 private:
  int x_{ };
  const int y_{ Renderer::kVirtualHeight - 20 };
  // InputComponent
  // PhysicsComponent
  // GraphicsComponent
};

#endif  // SRC_ENTITY_PADDLE_H_
