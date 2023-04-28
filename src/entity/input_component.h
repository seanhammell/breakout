#ifndef SRC_ENTITY_INPUT_COMPONENT_H_
#define SRC_ENTITY_INPUT_COMPONENT_H_

#include "SDL2/SDL.h"

class Paddle;

class InputComponent {
 public:
  const int kPaddleVelocity{ 10 };

  InputComponent() = default;

  ~InputComponent() = default;

  // Updates a Paddle's velocity based on user input.
  void Update(Paddle *paddle, SDL_Event input);
};

#endif  // SRC_ENTITY_INPUT_COMPONENT_H_
