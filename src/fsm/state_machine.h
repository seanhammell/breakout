#ifndef SRC_FSM_STATE_MACHINE_H_
#define SRC_FSM_STATE_MACHINE_H_

#include "SDL2/SDL.h"

class StateMachine {
 public:
  virtual ~StateMachine() {}

  virtual StateMachine *HandleInput(SDL_Event) { return NULL; }
  virtual void Update() {}
  virtual void Render() {}
};

#endif  // SRC_FSM_STATE_MACHINE_H_
