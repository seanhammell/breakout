#ifndef SRC_STATE_LEVEL_SELECT_H_
#define SRC_STATE_LEVEL_SELECT_H_

#include "SDL2/SDL.h"

#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

class LevelSelect : public StateMachine {
 public:
  explicit LevelSelect(StateMachine::States next);

  ~LevelSelect();

  // Allows the user to move between level options.
  void HandleInput(SDL_Event input) override;

  // Tracks the currently selected option and triggers when the user makes a
  // selection.
  StateMachine *Update() override;

  // Renders the header and levels to the screen.
  void Render() override;

 private:
  Widget title_{ };
  Textbox levels_{ };
  StateMachine::States next_{ kNoState };
  int selection_{ 1 };
  bool trigger_{ false };
};

#endif  // SRC_STATE_LEVEL_SELECT_H_
