#include "src/state/menu_state.h"

#include "SDL2/SDL.h"

#include "src/state/state_machine.h"
#include "src/graphic/texture.h"
#include "src/graphic/ui_element.h"

MenuState::MenuState() {
  title_ = UIElement(&texture_, {0, 0, 142, 16}, 25, 40);
}

bool MenuState::Load() {
  return texture_.LoadFromFile("./img/menu.png");
}

StateMachine *MenuState::HandleInput(SDL_Event input) {
  if (input.type == SDL_KEYDOWN) {
    if (input.key.keysym.sym == SDLK_SPACE) {
      return new MenuState();
    }
  }

  return NULL;
}

void MenuState::Render() {
  title_.Render();
}
