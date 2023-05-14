#ifndef SRC_STATE_SELECT_STATE_H_
#define SRC_STATE_SELECT_STATE_H_

#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"

class SelectState : public StateMachine {
 public:
  SelectState();

  ~SelectState() = default;

  // Loads the textures and font nedded by SelectState.
  static bool Load();
  
  // Responds to user input during level selection.
  void HandleInput(SDL_Event) override {}

  // Moves to the level editor for the desired level.
  StateMachine *Update() override { return NULL; }

  // Renders the prompt and level options.
  void Render() override;

 private:
  static inline Texture prompt_texture_{ };

  UIElement prompt_{ };
};

#endif  // SRC_STATE_SELECT_STATE_H_
