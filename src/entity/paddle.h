#ifndef SRC_ENTITY_PADDLE_H_
#define SRC_ENTITY_PADDLE_H_

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Paddle {
 public:
  Paddle() = default;
  Paddle(Texture *texture, SDL_Rect clip = {0, 8, 64, 8});
  ~Paddle() {}

  // Updates the paddle with any changes since the last frame.
  void Update();

 private:
  int x_{ };
  const int y_{ Renderer::kVirtualHeight - 20 };
  // InputComponent input_;
  // PhysicsComponent physics_;
  GraphicsComponent graphics_{ };
};

#endif  // SRC_ENTITY_PADDLE_H_
