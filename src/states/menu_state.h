#ifndef SRC_STATES_MENU_STATE_H_
#define SRC_STATES_MENU_STATE_H_

#include <SDL2/SDL.h>

#include "src/states/state.h"

class MenuState final : public State {
 public:
  ~MenuState() override;

  State *HandleInput(const StateMachine& fsm, SDL_Event input) override;
  void Update() override;
};

#endif  // SRC_STATES_MENU_STATE_H_
