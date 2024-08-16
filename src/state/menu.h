#ifndef SRC_STATE_MENU_H_
#define SRC_STATE_MENU_H_

#include "SDL2/SDL.h"
#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

class Menu : public StateMachine {
 public:
  Menu();

  ~Menu();

  // Responds to user input at the main menu.
  void HandleInput(SDL_Event input) override;

  // There is nothing to update at the main menu.
  StateMachine *Update() override;

  // Renders the title and prompt.
  void Render() override;

 private:
  Widget title_{};
  Textbox play_{};
  Textbox edit_{};
  StateMachine::States selection_{kPlayState};
};

#endif  // SRC_STATE_MENU_H_
