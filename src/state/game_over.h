#ifndef SRC_STATE_GAME_OVER_H_
#define SRC_STATE_GAME_OVER_H_

#include "SDL2/SDL.h"

#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

class GameOver : public StateMachine {
 public:
  explicit GameOver(int score);

  ~GameOver() = default;

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
  Textbox quit_{ };
};

#endif  // SRC_STATE_GAME_OVER_H_
