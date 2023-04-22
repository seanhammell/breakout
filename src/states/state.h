#ifndef SRC_STATES_STATE_H_
#define SRC_STATES_STATE_H_

#include <SDL2/SDL.h>

#include "src/states/state_machine.h"

class State {
 public:
  virtual ~State() {}

  virtual State *HandleInput(const StateMachine& fsm, SDL_Event input);
  virtual void Update();
};

#endif  // SRC_STATES_STATE_H_
