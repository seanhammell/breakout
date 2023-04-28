#ifndef SRC_ENTITY_PADDLE_H_
#define SRC_ENTITY_PADDLE_H_

#include "SDL2/SDL.h"

#include "src/entity/graphics_component.h"
#include "src/entity/input_component.h"
#include "src/graphic/renderer.h"
#include "src/graphic/texture.h"

class Paddle {
 public:
  const int y_{ Renderer::kVirtualHeight - 20 };

  Paddle() = default;
  Paddle(Texture *texture, SDL_Rect clip = {16, 6, 32, 4});

  ~Paddle() = default;

  // Setters.
  void set_velocity(int velocity);

  // Updates the Paddle with one frame of behavior.
  void Update(SDL_Event input);

  // Renders the Paddle to the screen.
  void Render();

 private:
  int x_{ 0 };
  int velocity_{ 0 };
  InputComponent input_{ };
  // PhysicsComponent physics_;
  GraphicsComponent graphics_{ };
};

#endif  // SRC_ENTITY_PADDLE_H_
