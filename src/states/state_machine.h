#ifndef SRC_STATES_STATE_MACHINE_H_
#define SRC_STATES_STATE_MACHINE_H_

#include <SDL2/SDL.h>

#include "src/states/state.h"

class StateMachine {
 public:
  StateMachine() {}
  ~StateMachine() {}

  void HandleInput(SDL_Event input);
  
 private:
  State *state_;
};

#endif  // SRC_STATES_STATE_MACHINE_H_