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
  // The paddle is actually 32x4 but because the Renderer is scaled down by
  // a factor of 4 from the actual window we set the width as 64x8.
  static const int kWidth{ 64 };
  static const int kHeight{ 8 };

  Paddle() = default;
  Paddle(Texture *texture, SDL_Rect clip = {16, 6, kWidth / 2, kHeight / 2});

  ~Paddle() = default;

  int get_x();
  int get_velocity();

  void set_x(int x);
  void set_velocity(int velocity);

  // Handles user input for the paddle.
  void HandleInput(SDL_Event input);

  // Updates the Paddle with one frame of behavior.
  void Update();

 private:
  int x_{ 0 };
  const int y_{ Renderer::kVirtualHeight - 20 };
  int velocity_{ 0 };
  InputComponent input_{ };
  PhysicsComponent physics_{ };
  GraphicsComponent graphics_{ };
};

#endif  // SRC_ENTITY_PADDLE_H_
