#ifndef SRC_STATE_MENU_STATE_H_
#define SRC_STATE_MENU_STATE_H_

#include "SDL2/SDL.h"

#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"
#include "src/ui/widget.h"

class MenuState : public StateMachine {
 public:
  MenuState();

  ~MenuState() = default;

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
  static inline Texture prompt_texture_{ };

  Widget title_{ };
  UIElement prompt_{ };
};

#endif  // SRC_STATE_MENU_STATE_H_
