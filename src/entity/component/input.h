#ifndef SRC_ENTITY_COMPONENT_INPUT_H_
#define SRC_ENTITY_COMPONENT_INPUT_H_

#include "SDL2/SDL.h"

class Paddle;

class InputComponent {
 public:
  const int kPaddleVelocity{ 4 };

  InputComponent() = default;

  ~InputComponent() = default;

  // Updates a Paddle's velocity based on user input.
  void Update(Paddle *paddle, SDL_Event input);
};

#endif  // SRC_ENTITY_COMPONENT_INPUT_H_
