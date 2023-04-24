#ifndef SRC_FSM_MENU_STATE_H_
#define SRC_FSM_MENU_STATE_H_

#include "SDL2/SDL.h"

#include "src/fsm/state_machine.h"

class MenuState : public StateMachine {
 public:
  MenuState() {}
  ~MenuState() {}

  StateMachine *HandleInput(SDL_Event input) override;
  void Update() override {}
  void Render() override {}
};

#endif  // SRC_FSM_MENU_STATE_H_
