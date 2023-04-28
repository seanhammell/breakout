#ifndef SRC_STATE_STATE_MACHINE_H_
#define SRC_STATE_STATE_MACHINE_H_

#include "SDL2/SDL.h"

class StateMachine {
 public:
  virtual ~StateMachine() = default;

  virtual StateMachine *HandleInput(SDL_Event) = 0;
  virtual void Update() = 0;
};

#endif  // SRC_STATE_STATE_MACHINE_H_
