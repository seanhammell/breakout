#ifndef SRC_STATE_MENU_STATE_H_
#define SRC_STATE_MENU_STATE_H_

#include "SDL2/SDL.h"

#include "src/graphic/font.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"
#include "src/state/state_machine.h"

class MenuState : public StateMachine {
 public:
  MenuState();

  ~MenuState() = default;

  // Loads the textures and font needed by MenuState.
  static bool Load();

  // Responds to user input while in MenuState.
  StateMachine *HandleInput(SDL_Event input) override;

  // Renders the title and prompt to the screen.
  void Update() override;

 private:
  static inline Font font_{ };
  static inline Texture title_texture_{ };
  static inline Texture prompt_texture_{ };

  UIElement title_{ };
  UIElement prompt_{ };
};

#endif  // SRC_STATE_MENU_STATE_H_
