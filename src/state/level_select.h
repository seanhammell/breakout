#ifndef SRC_STATE_LEVEL_SELECT_H_
#define SRC_STATE_LEVEL_SELECT_H_

#include "SDL2/SDL.h"

#include "src/state/state_machine.h"
#include "src/ui/textbox.h"
#include "src/ui/widget.h"

class LevelSelect : public StateMachine {
 public:
  explicit LevelSelect(StateMachine::States next);

  ~LevelSelect() = default;

  void HandleInput(SDL_Event input) override;

  StateMachine *Update() override;

  void Render() override;

 private:
  Widget title_{ };
  Textbox levels_{ };
};

#endif  // SRC_STATE_LEVEL_SELECT_H_
