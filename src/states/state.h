#ifndef SRC_STATES_STATE_H_
#define SRC_STATES_STATE_H_

#include <SDL2/SDL.h>

#include "src/states/state_machine.h"

class State {
 public:
  virtual ~State() {}

  virtual void HandleInput(StateMachine& state_machine, SDL_Event input);
};

#endif  // SRC_STATES_STATE_H_
