#ifndef SRC_STATE_MENU_STATE_H_
#define SRC_STATE_MENU_STATE_H_

#include "SDL2/SDL.h"

#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"

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

#endif  // SRC_STATE_MENU_STATE_H_
