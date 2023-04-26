#ifndef SRC_FSM_MENU_STATE_H_
#define SRC_FSM_MENU_STATE_H_

#include "SDL2/SDL.h"

#include "src/ecs/graphics_component.h"
#include "src/fsm/state_machine.h"

class MenuState : public StateMachine {
 public:
  MenuState();
  ~MenuState() {}

  // Handles user input at the main menu.
  StateMachine *HandleInput(SDL_Event input) override;

  // Updates the menu with any changes since the previous call.
  void Update() override;

 private:
  GraphicsComponent *graphics_{ NULL };
};

#endif  // SRC_FSM_MENU_STATE_H_
