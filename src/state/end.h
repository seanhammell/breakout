#ifndef SRC_STATE_END_H_
#define SRC_STATE_END_H_

#include "SDL2/SDL.h"

#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

class End : public StateMachine {
 public:
  explicit End(int score, bool victory);

  ~End();

  // Responds to user input at the main menu.
  void HandleInput(SDL_Event input) override;

  // Returns the new state based on user selection.
  StateMachine *Update() override;

  // Renders the title and prompt.
  void Render() override;

 private:
  Widget title_{ };
  Textbox score_{ };
  Textbox play_{ };
  Textbox menu_{ };
  StateMachine::States selection_{ kPlayState };
};

#endif  // SRC_STATE_END_H_
