#ifndef SRC_STATE_OVER_STATE_H_
#define SRC_STATE_OVER_STATE_H_

#include "SDL2/SDL.h"

#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"

class OverState : public StateMachine {
 public:
  OverState();

  ~OverState() = default;

  // Loads the textures and font needed by MenuState.
  static bool Load();

  // Responds to user input at the main menu.
  void HandleInput(SDL_Event input) override;

  // There is nothing to update at the main menu.
  StateMachine *Update() override;

  // Renders the title and prompt.
  void Render() override;

 private:
  static inline Font font_{ };
  static inline Texture title_texture_{ };
  static inline Texture play_texture_{ };
  static inline Texture quit_texture_{ };

  UIElement title_{ };
  UIElement score_display_{ };
  UIElement play_prompt_{ };
  UIElement quit_prompt_{ };
};

#endif  // SRC_STATE_OVER_STATE_H_