#ifndef SRC_FSM_STATE_MACHINE_H_
#define SRC_FSM_STATE_MACHINE_H_

#include "SDL2/SDL.h"

class StateMachine {
 public:
  virtual ~StateMachine() {}

  virtual StateMachine *HandleInput(SDL_Event) = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
};

#endif  // SRC_FSM_STATE_MACHINE_H_
