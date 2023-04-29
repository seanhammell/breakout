#ifndef SRC_ENTITY_PADDLE_H_
#define SRC_ENTITY_PADDLE_H_

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/entity/input_component.h"
#include "src/entity/physics_component.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Paddle {
 public:
  friend class InputComponent;
  friend class PhysicsComponent;

  Paddle() = default;
  Paddle(Texture *texture, SDL_Rect clip = {16, 6, 32, 4});

  ~Paddle() = default;

  // Handles user input for the paddle.
  void HandleInput(SDL_Event input);

  // Updates the Paddle with one frame of behavior.
  void Update();

 private:
  int x_{ 0 };
  const int y_{ Renderer::kVirtualHeight - 20 };
  int width_{ 0 };
  int height_{ 0 };
  int velocity_{ 0 };
  InputComponent input_{ };
  PhysicsComponent physics_{ };
  GraphicsComponent graphics_{ };
};

#endif  // SRC_ENTITY_PADDLE_H_
