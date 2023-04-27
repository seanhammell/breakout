#ifndef SRC_FSM_MENU_STATE_H_
#define SRC_FSM_MENU_STATE_H_

#include "SDL2/SDL.h"

#include "src/fsm/state_machine.h"
#include "src/gfx/texture.h"
#include "src/gfx/ui_element.h"

class MenuState : public StateMachine {
 public:
  MenuState();
  ~MenuState() {}

  // Loads all resources needed for the menu.
  static bool Load();

  // Handles user input at the menu.
  StateMachine *HandleInput(SDL_Event input) override;

  // Update the menu with any changes since the last frame.
  void Update() override {}

  // Render the menu to the screen.
  void Render() override;

 private:
  static inline Texture texture_{ };
  UIElement title_;
};

#endif  // SRC_FSM_MENU_STATE_H_
