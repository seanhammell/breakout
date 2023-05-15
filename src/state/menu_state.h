#ifndef SRC_STATE_MENU_STATE_H_
#define SRC_STATE_MENU_STATE_H_

#include "SDL2/SDL.h"

#include "src/state/state_machine.h"
#include "src/ui/widget.h"
#include "src/ui/textbox.h"

class MenuState : public StateMachine {
 public:
  MenuState();

  ~MenuState();

  // Responds to user input at the main menu.
  void HandleInput(SDL_Event input) override;

  // There is nothing to update at the main menu.
  StateMachine *Update() override;

  // Renders the title and prompt.
  void Render() override;

 private:
  Widget title_{ };
  Textbox play_{ };
};

#endif  // SRC_STATE_MENU_STATE_H_
